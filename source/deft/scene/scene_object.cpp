#include "scene/scene_object.h"

#include "log/log.h"

namespace deft {

SceneObject::SceneObject(const std::shared_ptr<Model>& model,
                         const Transform& transform, bool isLight)
    : _model(model), _entityId(g_registry.createEntity()) {
  g_registry.addComponent<Transform>(_entityId, transform);
  g_registry.addComponent<Renderable>(_entityId, Renderable(model));
  g_registry.addComponent<MaterialComp>(
      _entityId, MaterialComp({1.0f, 0.5f, 0.31f}, {1.0f, 0.5f, 0.31f},
                              {0.5f, 0.5f, 0.5f}, 32.0f));
  if (isLight) {
    g_registry.addComponent<LightDetail>(
        _entityId, LightDetail({0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f},
                               {1.0f, 1.0f, 1.0f}));
  }
}

SceneObject::~SceneObject() { g_registry.destroyEntity(_entityId); }

Entity& SceneObject::getEntityId() { return _entityId; }

std::shared_ptr<Model>& SceneObject::getModel() {
  return g_registry.getComponent<Renderable>(_entityId).model;
}

Transform& SceneObject::getTransform() {
  return g_registry.getComponent<Transform>(_entityId);
}

void SceneObject::setLight(bool flag) {
  if (flag) {
    g_registry.addComponent<LightDetail>(
        _entityId, LightDetail({0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f},
                               {1.0f, 1.0f, 1.0f}));
  } else {
    g_registry.removeComponent<LightDetail>(_entityId);
  }
}

bool SceneObject::isLight() {
  return g_registry.haveComponent<LightDetail>(_entityId);
}

}  // namespace deft
