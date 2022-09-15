#ifndef __DEFT_RENDERABLE_H__
#define __DEFT_RENDERABLE_H__

#include <memory>

#include "ecs/components/component.h"
#include "render/model.h"
#include "render/texture.h"

namespace deft {

class MeshComponent : public Component {
 public:
  std::shared_ptr<Mesh> mesh;

  MeshComponent() = default;
};

}  // namespace deft

#endif  // __DEFT_RENDERABLE_H__