#ifndef __DEFT_CAMERA_CONTROLLER_H__
#define __DEFT_CAMERA_CONTROLLER_H__

#include <memory>

#include "ecs/components/transform.h"
#include "math/math.h"
#include "render/camera.h"

namespace deft {

class CameraController {
 public:
  CameraController();
  ~CameraController();

  std::shared_ptr<Camera> getCamera() const;

  void moveFront();
  void moveBack();
  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();

  void tick(float dt);

  void move(float dt);

  void          setPosition(const math::Vector3& position);
  math::Vector3 getPosition();

  void setLookDirection(const math::Vector3& direction);

  void setEnable(bool flag);
  bool isEnable();

 private:
  void handleKey();
  void handleScroll(double x, double y);
  void handleMouseMove();

 private:
  bool _enabled;
  bool _keyPressed;

  math::Vector3 _moveDir;
  math::Vector3 _intertiaDir;

  std::shared_ptr<Camera> _camera;

  std::shared_ptr<CameraTransform> _transform;

  float _moveSpeed;
  float _maxSpeed;
  float _deltaSpeed;  // 镜头惯性速度大小，目前只在水平方向有效果
  float _scrollSpeed;
  float _mouseSensitivity;
};

}  // namespace deft
#endif  // __DEFT_CAMERA_CONTROLLER_H__