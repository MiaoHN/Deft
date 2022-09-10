#include "controller/camera_controller.h"

#include "app/application.h"

namespace deft {

CameraController::CameraController() {
  _transform                = std::make_shared<CameraTransform>();
  _transform->up            = {0.0f, 1.0f, 0.0f};
  _transform->position      = {0.0f, 0.0f, 0.0f};
  _transform->lookDirection = {0.0f, 0.0f, -1.0f};

  _transform->yaw   = -90.0f;
  _transform->pitch = 0.0f;
  _transform->fov   = 45.0f;

  _camera = std::make_shared<Camera>(_transform);

  _enabled = false;

  _moveSpeed        = 0.0f;
  _maxSpeed         = 2.0f;
  _deltaSpeed       = 0.5f;
  _scrollSpeed      = 2.0f;
  _mouseSensitivity = 0.1f;

  Application::Get().getInputManager().addScrollCallback(
      "CameraController::handleScroll",
      std::bind(CameraController::handleScroll, this, std::placeholders::_1,
                std::placeholders::_2));
}

CameraController::~CameraController() {}

std::shared_ptr<Camera> CameraController::getCamera() const { return _camera; }

void CameraController::moveFront() { _moveDir += _transform->lookDirection; }

void CameraController::moveBack() { _moveDir -= _transform->lookDirection; }

void CameraController::moveRight() {
  _moveDir += _transform->lookDirection.cross(_transform->up);
}

void CameraController::moveLeft() {
  _moveDir -= _transform->lookDirection.cross(_transform->up);
}

void CameraController::moveUp() { _moveDir += _transform->up; }

void CameraController::moveDown() { _moveDir -= _transform->up; }

void CameraController::tick(float dt) {
  if (!_enabled) return;

  handleKey();
  handleMouseMove();

  move(dt);
  if (_keyPressed) {
    _intertiaDir = _moveDir;
    _moveSpeed += _deltaSpeed;
    _moveSpeed = std::min(_moveSpeed, _maxSpeed);
  } else {
    _moveSpeed -= _deltaSpeed;
    _moveSpeed = std::max(_moveSpeed, 0.0f);
  }
  _moveDir = {0.0f};
}

void CameraController::move(float dt) {
  if (_keyPressed) {
    _transform->position += _moveDir * dt * _moveSpeed;
  } else {
    _transform->position += _intertiaDir * dt * _moveSpeed;
  }
}

void CameraController::setPosition(const math::Vector3& position) {
  _transform->position = position;
}

math::Vector3 CameraController::getPosition() { return _transform->position; }

void CameraController::setLookDirection(const math::Vector3& direction) {
  _transform->lookDirection = direction.normalized();
}

void CameraController::setEnable(bool flag) { _enabled = flag; }

bool CameraController::isEnable() { return _enabled; }

void CameraController::handleKey() {
  _keyPressed = false;
  if (IS_KEY_PRESS(KeyCode::A)) {
    _keyPressed = true;
    moveLeft();
  } else if (IS_KEY_PRESS(KeyCode::D)) {
    _keyPressed = true;
    moveRight();
  }
  if (IS_KEY_PRESS(KeyCode::W)) {
    _keyPressed = true;
    moveFront();
  } else if (IS_KEY_PRESS(KeyCode::S)) {
    _keyPressed = true;
    moveBack();
  }
  if (IS_KEY_PRESS(KeyCode::Space)) {
    _keyPressed = true;
    moveUp();
  } else if (IS_KEY_PRESS(KeyCode::LeftShift)) {
    _keyPressed = true;
    moveDown();
  }
}

void CameraController::handleScroll(double x, double y) {
  if (!isEnable()) return;
  if (y > -1e-7 && y < 1e-7) return;
  _transform->fov -= _scrollSpeed * y;

  if (_transform->fov < 5.0f) _transform->fov = 5.0f;
  if (_transform->fov > 100.0f) _transform->fov = 100.0f;
}

void CameraController::handleMouseMove() {
  math::Vector2 offset = GET_CURSOR_OFFSET();
  _transform->yaw += offset.x * _mouseSensitivity;
  _transform->pitch -= offset.y * _mouseSensitivity;

  if (_transform->pitch > 89.0f) {
    _transform->pitch = 89.0f;
  }
  if (_transform->pitch < -89.0f) {
    _transform->pitch = -89.0f;
  }

  _transform->reCalculate();
}

}  // namespace deft
