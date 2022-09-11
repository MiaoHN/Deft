#include "scene/scene_object.h"

#include "log/log.h"

namespace deft {

SceneObject::SceneObject(const std::shared_ptr<Model>& model,
                         const Transform&              transform)
    : _model(model), _entityId(g_registry.createEntity()) {
  g_registry.addComponent<Transform>(_entityId, transform);
  LOG_CORE_INFO("entity id = %d", static_cast<int>(_entityId));
}

SceneObject::~SceneObject() {}

std::shared_ptr<Model>& SceneObject::getModel() { return _model; }

Transform& SceneObject::getTransform() {
  auto& transform = g_registry.getComponent<Transform>(_entityId);
  return transform;
}

}  // namespace deft
