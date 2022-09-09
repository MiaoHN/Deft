#ifndef __DEFT_TRANSFORM_H__
#define __DEFT_TRANSFORM_H__

#include "math/math.h"

namespace deft {

struct Transform {
  math::Vector3 position;

  Transform() = default;
  Transform(const math::Vector3& position_) : position(position_) {}
};

struct CameraTransform : public Transform {
  float         yaw;
  float         pitch;
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
      : Transform(position_),
        yaw(yaw_),
        pitch(pitch_),
        up(up_),
        lookDirection(lookDirection_) {}
};

}  // namespace deft

#endif  // __DEFT_TRANSFORM_H__