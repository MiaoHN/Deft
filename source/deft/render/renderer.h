#ifndef __DEFT_RENDERER_H__
#define __DEFT_RENDERER_H__

#include <memory>

#include "math/math.h"
#include "render/camera.h"
#include "render/model.h"
#include "render/shader.h"
#include "render/texture.h"

namespace deft {

class Renderer {
 public:
  void begin(std::shared_ptr<Camera> camera);

  void submit(const std::shared_ptr<Model>&   model,
              const std::shared_ptr<Shader>&  shader,
              const std::shared_ptr<Texture>& texture,
              const math::Vector3&            position);

  void end();

 private:
  math::Matrix4 _proj;
  math::Matrix4 _view;
};

}  // namespace deft

#endif  // __DEFT_RENDERER_H__