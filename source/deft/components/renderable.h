#ifndef __DEFT_RENDERABLE_H__
#define __DEFT_RENDERABLE_H__

#include <memory>

#include "render/model.h"
#include "render/texture.h"

namespace deft {

struct Renderable {
  std::shared_ptr<Model> model;
  Renderable() = default;
  Renderable(const std::shared_ptr<Model>& model) : model(model) {}
};

}  // namespace deft

#endif  // __DEFT_RENDERABLE_H__