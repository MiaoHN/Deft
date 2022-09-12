#ifndef __DEFT_BOX_H__
#define __DEFT_BOX_H__

#include "math/math.h"
#include "scene/scene_object.h"

namespace deft {

class Box : public SceneObject {
 public:
  Box(const math::Vector3& position, bool isLight = false);
  Box(const math::Vector3& position, const math::Vector3& color,
      bool isLight = false);
  ~Box();
};

}  // namespace deft

#endif  // __DEFT_BOX_H__