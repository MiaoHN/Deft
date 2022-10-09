#ifndef __DEFT_CAMERA_H__
#define __DEFT_CAMERA_H__

#include <memory>

#include "ecs/components/transform.h"
#include "core/math/math.h"

namespace deft {

class Camera {
 public:
  Camera();

  const math::Matrix4& getProjection() const;
  const math::Matrix4& getView() const;
  const math::Vector3& getPosition() const;

 protected:
  math::Matrix4 _projection;
  math::Matrix4 _view;

  math::Vector3 _position;
};

}  // namespace deft

#endif  // __DEFT_CAMERA_H__