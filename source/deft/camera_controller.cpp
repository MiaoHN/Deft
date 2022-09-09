#include "camera_controller.h"

namespace deft {

CameraController::CameraController() {
  _transform                = std::make_shared<CameraTransform>();
  _transform->position      = {0.0f, 0.0f, 0.0f};
  _transform->lookDirection = {0.0f, 0.0f, -1.0f};

  _transform->yaw   = -90.0f;
  _transform->pitch = 0.0f;

  _camera = std::make_shared<Camera>(_transform);

  _moveSpeed = 1.0f;
}

CameraController::~CameraController() {}

std::shared_ptr<Camera> CameraController::getCamera() const { return _camera; }

void CameraController::move(const math::Vector3& direction, float dt) {
  if (direction.length() < 1e-7) return;
  _transform->position += math::normalize(direction) * dt * _moveSpeed;
}

void CameraController::setPosition(const math::Vector3& position) {
  _transform->position = position;
}

math::Vector3 CameraController::getPosition() { return _transform->position; }

void CameraController::setLookDirection(const math::Vector3& direction) {
  _transform->lookDirection = direction.normalized();
}

}  // namespace deft
