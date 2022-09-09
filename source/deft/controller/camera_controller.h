#ifndef __DEFT_CAMERA_CONTROLLER_H__
#define __DEFT_CAMERA_CONTROLLER_H__

#include <memory>

#include "components/transform.h"
#include "math/math.h"
#include "render/camera.h"

namespace deft {

class CameraController {
 public:
  CameraController();
  ~CameraController();

  std::shared_ptr<Camera> getCamera() const;

  void move(const math::Vector3& direction, float dt);

  void          setPosition(const math::Vector3& position);
  math::Vector3 getPosition();

  void setLookDirection(const math::Vector3& direction);

 private:
  std::shared_ptr<Camera> _camera;

  std::shared_ptr<CameraTransform> _transform;

  float _moveSpeed;
};

}  // namespace deft

#endif  // __DEFT_CAMERA_CONTROLLER_H__