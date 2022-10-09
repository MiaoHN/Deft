#ifndef __DEFT_TRANSFORM_H__
#define __DEFT_TRANSFORM_H__

#include "ecs/components/component.h"
#include "core/math/math.h"

namespace deft {

class TransformComponent : public Component {
 public:
  math::Vector3 position;
  math::Vector3 rotation;
  math::Vector3 scale{1.0f, 1.0f, 1.0f};

  inline math::Matrix4 getTransform() const {
    return math::translate(math::Matrix4(1.0f), position) * getRotation() *
           math::scale(math::Matrix4(1.0f), scale);
  }

  inline math::Matrix4 getRotation() const {
    return math::Quaternion(rotation).toMatrix4();
  }

  TransformComponent() = default;
  TransformComponent(const math::Vector3& position_) : position(position_) {}
};

}  // namespace deft

#endif  // __DEFT_TRANSFORM_H__