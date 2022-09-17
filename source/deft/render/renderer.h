#ifndef __DEFT_RENDERER_H__
#define __DEFT_RENDERER_H__

#include <memory>

#include "ecs/components/mesh.h"
#include "ecs/components/transform.h"
#include "ecs/ecs.h"
#include "math/math.h"
#include "render/camera.h"
#include "render/frame_buffer.h"
#include "render/mesh.h"
#include "render/model.h"
#include "render/shader.h"
#include "render/texture.h"

namespace deft {

class Renderer {
 public:
  static void Init();

  static void Begin(std::shared_ptr<Camera> camera);

  static void Submit(const TransformComponent&      transform,
                     const MeshComponent&           meshComponent,
                     const std::shared_ptr<Shader>& shader,
                     const Entity&                  entity);

  static void End();
};

}  // namespace deft

#endif  // __DEFT_RENDERER_H__