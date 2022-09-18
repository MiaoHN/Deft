#ifndef __DEFT_EDITOR_CAMERA_H__
#define __DEFT_EDITOR_CAMERA_H__

#include "deft.h"

namespace deft {

class EditorCamera : public Camera {
 public:
  EditorCamera() {
    _up            = {0.0f, 1.0f, 0.0f};
    _position      = {0.0f, 0.0f, 0.0f};
    _lookDirection = {0.0f, 0.0f, -1.0f};

    _yaw   = -90.0f;
    _pitch = 0.0f;
    _fov   = 45.0f;

    _aspect = 16.0f / 9.0f;  // temp

    _enabled = false;

    _moveSpeed        = 2.0f;
    _scrollSpeed      = 2.0f;
    _mouseSensitivity = 0.1f;

    _projection = math::perspective(_fov, _aspect, 0.1f, 10000.0f);
  }
  ~EditorCamera() {}

  void tick(float dt) {
    // Mouse
    static math::Vector2 currentPos = Input::GetMousePosition();
    auto                 newPos     = Input::GetMousePosition();

    math::Vector2 offset = newPos - currentPos;
    currentPos           = newPos;

    if (!_enabled) {
      return;
    }

    _yaw += offset.x * _mouseSensitivity;
    _pitch -= offset.y * _mouseSensitivity;

    if (_pitch > 89.0f) {
      _pitch = 89.0f;
    }
    if (_pitch < -89.0f) {
      _pitch = -89.0f;
    }

    reCalculate();

    // Key
    math::Vector3 moveDir(0.0f);
    if (Input::IsKeyPress(KeyCode::A)) {
      moveDir -= _lookDirection.cross(_up);
    } else if (Input::IsKeyPress(KeyCode::D)) {
      moveDir += _lookDirection.cross(_up);
    }
    if (Input::IsKeyPress(KeyCode::W)) {
      moveDir += _lookDirection;
    } else if (Input::IsKeyPress(KeyCode::S)) {
      moveDir -= _lookDirection;
    }
    if (Input::IsKeyPress(KeyCode::Space)) {
      moveDir += _up;
    } else if (Input::IsKeyPress(KeyCode::LeftShift)) {
      moveDir -= _up;
    }
    if (moveDir.length() > 1e-7) {
      moveDir.normalized();
    }

    _position += moveDir * dt * _moveSpeed;

    _view = math::lookAt(_position, _position + _lookDirection, _up);
  }

  const math::Matrix4& getView() const { return _view; }

  void setEnable(bool flag) { _enabled = flag; }
  bool isEnabled() const { return _enabled; }

 private:
  void reCalculate() {
    math::Vector3 front;
    front.x        = cos(math::radians(_yaw)) * cos(math::radians(_pitch));
    front.y        = sin(math::radians(_pitch));
    front.z        = sin(math::radians(_yaw)) * cos(math::radians(_pitch));
    _lookDirection = math::normalize(front);
    auto right =
        math::normalize(math::cross(_lookDirection, {0.0f, 1.0f, 0.0f}));
    _up = math::normalize(math::cross(right, _lookDirection));
  }

 private:
  math::Vector3 _up;
  math::Vector3 _lookDirection;

  float _yaw;
  float _pitch;
  float _fov;
  float _aspect;

  bool _enabled;

  float _mouseSensitivity;
  float _moveSpeed;
  float _scrollSpeed;
};

}  // namespace deft

#endif  // __DEFT_EDITOR_CAMERA_H__