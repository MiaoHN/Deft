#include "scene/scene_object.h"

#include "log/log.h"

namespace deft {

SceneObject::SceneObject(const std::shared_ptr<Model>& model,
                         const Transform&              transform)
    : _model(model), _entityId(g_registry.createEntity()) {
  g_registry.addComponent<Transform>(_entityId, transform);
  g_registry.addComponent<Renderable>(_entityId, Renderable(model));
}

SceneObject::~SceneObject() {}

std::shared_ptr<Model>& SceneObject::getModel() {
  return g_registry.getComponent<Renderable>(_entityId).model;
}

Transform& SceneObject::getTransform() {
  return g_registry.getComponent<Transform>(_entityId);
}

}  // namespace deft
