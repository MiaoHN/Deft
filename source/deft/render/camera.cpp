#include "render/camera.h"

#include "core/application.h"
#include "pch.h"

namespace deft {

Camera::Camera() {}

const math::Matrix4& Camera::getProjection() const { return _projection; }
const math::Matrix4& Camera::getView() const { return _view; }
const math::Vector3& Camera::getPosition() const { return _position; }

}  // namespace deft
