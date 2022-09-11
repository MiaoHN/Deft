#ifndef __DEFT_RENDERABLE_H__
#define __DEFT_RENDERABLE_H__

#include <memory>

#include "render/model.h"
#include "render/texture.h"

namespace deft {

struct LightDetail {
  math::Vector3 ambient;
  math::Vector3 diffuse;
  math::Vector3 specular;
  LightDetail() = default;
  LightDetail(const math::Vector3 &ambient, const math::Vector3 &diffuse,
              const math::Vector3 &specular)
      : ambient(ambient), diffuse(diffuse), specular(specular) {}
};

struct MaterialComp {
  math::Vector3 ambient;
  math::Vector3 diffuse;
  math::Vector3 specular;
  float         shininess;
  MaterialComp() = default;
  MaterialComp(const math::Vector3 &ambient, const math::Vector3 &diffuse,
               const math::Vector3 &specular, float shininess)
      : ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess) {}
};

struct Renderable {
  std::shared_ptr<Model> model;
  Renderable() = default;
  Renderable(const std::shared_ptr<Model> &model) : model(model) {}
};

}  // namespace deft

#endif  // __DEFT_RENDERABLE_H__