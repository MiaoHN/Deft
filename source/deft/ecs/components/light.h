#ifndef __DEFT_COMPONENT_LIGHT_H__
#define __DEFT_COMPONENT_LIGHT_H__

#include "ecs/components/component.h"
#include "math/math.h"

namespace deft {

enum class LightType {
  Point,
  Direction,
  Spot,
};

class LightComponent : public Component {
 public:
  LightComponent() = default;

  LightType type;

  math::Vector3 ambient;
  math::Vector3 diffuse;
  math::Vector3 specular;

  // DirLight

  float constant;
  float linear;
  float quadratic;

  // PointLight

  float cutOff;
  float outerCutOff;

  // SpotLight
};

}  // namespace deft

#endif  // __DEFT_COMPONENT_LIGHT_H__