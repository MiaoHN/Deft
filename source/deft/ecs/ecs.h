#ifndef __DEFT_ECS_H__
#define __DEFT_ECS_H__

// https://austinmorlan.com/posts/entity_component_system/#the-entity

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

namespace deft {

using Entity = std::uint32_t;

const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
 public:
  EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
      _availableEntities.push(entity);
    }
  }

  Entity createEntity() {
    assert(_livingEntityCount < MAX_ENTITIES &&
           "Too many entities in existence.");

    // Take an ID from the front of the queue
    Entity id = _availableEntities.front();
    _availableEntities.pop();
    ++_livingEntityCount;

    return id;
  }

  void destroyEntity(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    _signatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    _availableEntities.push(entity);
    --_livingEntityCount;
  }

  void setSignature(Entity entity, Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Put this entity's signature into the array
    _signatures[entity] = signature;
  }

  Signature getSignature(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Get this entity's signature from the array
    return _signatures[entity];
  }

 private:
  // Queue of unused entity IDs
  std::queue<Entity> _availableEntities{};

  // Array of signatures where the index corresponds to the entity ID
  std::array<Signature, MAX_ENTITIES> _signatures{};

  // Total living entities - used to keep limits on how many exist
  uint32_t _livingEntityCount{};
};

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class IComponentArray {
 public:
  virtual ~IComponentArray()                  = default;
  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
 public:
  void insertData(Entity entity, T component) {
    assert(_entityToIndexMap.find(entity) == _entityToIndexMap.end() &&
           "Component added to same entity more than once.");

    // Put new entry at end and update the maps
    size_t newIndex             = _size;
    _entityToIndexMap[entity]   = newIndex;
    _indexToEntityMap[newIndex] = entity;
    _componentArray[newIndex]   = component;
    ++_size;
  }

  void removeData(Entity entity) {
    assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end() &&
           "Removing non-existent component.");

    // Copy element at end into deleted element's place to maintain density
    size_t indexOfRemovedEntity           = _entityToIndexMap[entity];
    size_t indexOfLastElement             = _size - 1;
    _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

    // Update map to point to moved spot
    Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
    _entityToIndexMap[entityOfLastElement]  = indexOfRemovedEntity;
    _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    _entityToIndexMap.erase(entity);
    _indexToEntityMap.erase(indexOfLastElement);

    --_size;
  }

  T& getData(Entity entity) {
    assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end() &&
           "Retrieving non-existent component.");

    // Return a reference to the entity's component
    return _componentArray[_entityToIndexMap[entity]];
  }

  void entityDestroyed(Entity entity) override {
    if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
      // Remove the entity's component if it existed
      removeData(entity);
    }
  }

 private:
  // The packed array of components (of generic type T),
  // set to a specified maximum amount, matching the maximum number
  // of entities allowed to exist simultaneously, so that each entity
  // has a unique spot.
  std::array<T, MAX_ENTITIES> _componentArray;

  // Map from an entity ID to an array index.
  std::unordered_map<Entity, size_t> _entityToIndexMap;

  // Map from an array index to an entity ID.
  std::unordered_map<size_t, Entity> _indexToEntityMap;

  // Total size of valid entries in the array.
  size_t _size;
};

class ComponentManager {
 public:
  template <typename T>
  void registerComponent() {
    const char* typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) == _componentTypes.end() &&
           "Registering component type more than once.");

    // Add this component type to the component type map
    _componentTypes.insert({typeName, _nextComponentType});

    // Create a ComponentArray pointer and add it to the component arrays map
    _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be
    // different
    ++_nextComponentType;
  }

  template <typename T>
  ComponentType getComponentType() {
    const char* typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) != _componentTypes.end() &&
           "Component not registered before use.");

    // Return this component's type - used for creating signatures
    return _componentTypes[typeName];
  }

  template <typename T>
  void addComponent(Entity entity, T component) {
    // Add a component to the array for an entity
    getComponentArray<T>()->insertData(entity, component);
  }

  template <typename T>
  void removeComponent(Entity entity) {
    // Remove a component from the array for an entity
    getComponentArray<T>()->removeData(entity);
  }

  template <typename T>
  T& getComponent(Entity entity) {
    // Get a reference to a component from the array for an entity
    return getComponentArray<T>()->getData(entity);
  }

  void entityDestroyed(Entity entity) {
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    for (auto const& pair : _componentArrays) {
      auto const& component = pair.second;

      component->entityDestroyed(entity);
    }
  }

 private:
  // Map from type string pointer to a component type
  std::unordered_map<const char*, ComponentType> _componentTypes{};

  // Map from type string pointer to a component array
  std::unordered_map<const char*, std::shared_ptr<IComponentArray>>
      _componentArrays{};

  // The component type to be assigned to the next registered component -
  // starting at 0
  ComponentType _nextComponentType{};

  // Convenience function to get the statically casted pointer to the
  // ComponentArray of type T.
  template <typename T>
  std::shared_ptr<ComponentArray<T>> getComponentArray() {
    const char* typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) != _componentTypes.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(
        _componentArrays[typeName]);
  }
};

class System {
 public:
  std::set<Entity> _entities;
};

class SystemManager {
 public:
  template <typename T>
  std::shared_ptr<T> registerSystem() {
    const char* typeName = typeid(T).name();

    assert(_systems.find(typeName) == _systems.end() &&
           "Registering system more than once.");

    // Create a pointer to the system and return it so it can be used externally
    auto system = std::make_shared<T>();
    _systems.insert({typeName, system});
    return system;
  }

  template <typename T>
  void setSignature(Signature signature) {
    const char* typeName = typeid(T).name();

    assert(_systems.find(typeName) != _systems.end() &&
           "System used before registered.");

    // Set the signature for this system
    _signatures.insert({typeName, signature});
  }

  void entityDestroyed(Entity entity) {
    // Erase a destroyed entity from all system lists
    // mEntities is a set so no check needed
    for (auto const& pair : _systems) {
      auto const& system = pair.second;

      system->_entities.erase(entity);
    }
  }

  void entitySignatureChanged(Entity entity, Signature entitySignature) {
    // Notify each system that an entity's signature changed
    for (auto const& pair : _systems) {
      auto const& type            = pair.first;
      auto const& system          = pair.second;
      auto const& systemSignature = _signatures[type];

      // Entity signature matches system signature - insert into set
      if ((entitySignature & systemSignature) == systemSignature) {
        system->_entities.insert(entity);
      }
      // Entity signature does not match system signature - erase from set
      else {
        system->_entities.erase(entity);
      }
    }
  }

 private:
  // Map from system type string pointer to a signature
  std::unordered_map<const char*, Signature> _signatures{};

  // Map from system type string pointer to a system pointer
  std::unordered_map<const char*, std::shared_ptr<System>> _systems{};
};

class Registry {
 public:
  void init() {
    // Create pointers to each manager
    _componentManager = std::make_unique<ComponentManager>();
    _entityManager    = std::make_unique<EntityManager>();
    _systemManager    = std::make_unique<SystemManager>();
  }

  // Entity methods
  Entity createEntity() {
    Entity entity = _entityManager->createEntity();
    _entities.push_back(entity);
    return entity;
  }

  void destroyEntity(Entity entity) {
    auto iter = std::find(_entities.begin(), _entities.end(), entity);
    _entities.erase(iter);

    _entityManager->destroyEntity(entity);

    _componentManager->entityDestroyed(entity);

    _systemManager->entityDestroyed(entity);
  }

  // Component methods
  template <typename T>
  void registerComponent() {
    _componentManager->registerComponent<T>();
  }

  template <typename T>
  void addComponent(Entity entity, T component) {
    _componentManager->addComponent<T>(entity, component);

    auto signature = _entityManager->getSignature(entity);
    signature.set(_componentManager->getComponentType<T>(), true);
    _entityManager->setSignature(entity, signature);

    _systemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T>
  void removeComponent(Entity entity) {
    _componentManager->removeComponent<T>(entity);

    auto signature = _entityManager->getSignature(entity);
    signature.set(_componentManager->getComponentType<T>(), false);
    _entityManager->setSignature(entity, signature);

    _systemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T>
  T& getComponent(Entity entity) {
    return _componentManager->getComponent<T>(entity);
  }

  template <typename T>
  ComponentType getComponentType() {
    return _componentManager->getComponentType<T>();
  }

  // System methods
  template <typename T>
  std::shared_ptr<T> registerSystem() {
    return _systemManager->registerSystem<T>();
  }

  template <typename T>
  void setSystemSignature(Signature signature) {
    _systemManager->setSignature<T>(signature);
  }

  std::vector<Entity>& getEntiesUsed() { return _entities; }

 private:
  std::unique_ptr<ComponentManager> _componentManager;
  std::unique_ptr<EntityManager>    _entityManager;
  std::unique_ptr<SystemManager>    _systemManager;

  std::vector<Entity> _entities;
};

extern Registry g_registry;

}  // namespace deft

#endif  // __DEFT_ECS_H__