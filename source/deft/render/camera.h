#ifndef __DEFT_CAMERA_H__
#define __DEFT_CAMERA_H__

#include <memory>

#include "math/math.h"
#include "transform.h"

namespace deft {

class Camera {
 public:
  Camera(const std::shared_ptr<CameraTransform>& transform);

  math::Matrix4 getView();
  math::Matrix4 getProjection();

 private:
  std::shared_ptr<CameraTransform> _transform;
};

}  // namespace deft

#endif  // __DEFT_CAMERA_H__