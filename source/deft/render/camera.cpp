#include "render/camera.h"

#include "core/application.h"
#include "pch.h"

namespace deft {

Camera::Camera(const std::shared_ptr<CameraTransform>& transform)
    : _transform(transform) {}

math::Matrix4 Camera::getView() {
  return math::lookAt(_transform->position,
                      _transform->position + _transform->lookDirection,
                      _transform->up);
}

math::Matrix4 Camera::getProjection() {
  float aspect = (float)Application::Get().getWindow().getWidth() /
                 (float)Application::Get().getWindow().getHeight();
  return math::perspective(math::radians(_transform->fov), aspect, 0.001f,
                           10000.0f);
}

math::Vector3 Camera::getPosition() { return _transform->position; }

}  // namespace deft
