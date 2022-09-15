#ifndef __DEFT_TRANSFORM_H__
#define __DEFT_TRANSFORM_H__

#include "ecs/components/component.h"
#include "math/math.h"

namespace deft {

class TransformComponent : public Component {
 public:
  math::Vector3 position;
  math::Vector3 rotation;
  math::Vector3 scale;

  TransformComponent() = default;
  TransformComponent(const math::Vector3& position_) : position(position_) {}
};

struct CameraTransform : public TransformComponent {
  float         yaw;
  float         pitch;
  float         fov;
  math::Vector3 up;
  math::Vector3 lookDirection;

  void reCalculate() {
    math::Vector3 front;
    front.x       = cos(math::radians(yaw)) * cos(math::radians(pitch));
    front.y       = sin(math::radians(pitch));
    front.z       = sin(math::radians(yaw)) * cos(math::radians(pitch));
    lookDirection = math::normalize(front);
    auto right =
        math::normalize(math::cross(lookDirection, {0.0f, 1.0f, 0.0f}));
    up = math::normalize(math::cross(right, lookDirection));
  }

  CameraTransform(const math::Vector3& position_ = {0.0f, 0.0f, 0.0f},  //

                  float yaw_   = -90.0f,  //
                  float pitch_ = 0.0f,    //

                  const math::Vector3& up_            = {0.0f, 1.0f, 0.0f},
                  const math::Vector3& lookDirection_ = {0.0f, 0.0f, -1.0f})
      : TransformComponent(position_),
        yaw(yaw_),
        pitch(pitch_),
        up(up_),
        lookDirection(lookDirection_) {}
};

}  // namespace deft

#endif  // __DEFT_TRANSFORM_H__