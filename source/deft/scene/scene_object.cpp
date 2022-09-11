#include "scene/scene_object.h"

namespace deft {

SceneObject::SceneObject(const std::shared_ptr<Model>&     model,
                         const std::shared_ptr<Transform>& transform)
    : _model(model), _transform(transform) {}

SceneObject::~SceneObject() {}

std::shared_ptr<Model>& SceneObject::getModel() { return _model; }

std::shared_ptr<Transform>& SceneObject::getTransform() { return _transform; }

}  // namespace deft
