#ifndef __DEFT_COMPONENT_TAG_H__
#define __DEFT_COMPONENT_TAG_H__

#include "ecs/components/component.h"

namespace deft {

class TagComponent : public Component {
 public:
  std::string name;

  TagComponent() = default;
};

}  // namespace deft

#endif  // __DEFT_COMPONENT_TAG_H__