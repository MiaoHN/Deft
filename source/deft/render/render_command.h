#ifndef __DEFT_RENDER_COMMAND_H__
#define __DEFT_RENDER_COMMAND_H__

#include <memory>

#include "math/math.h"
#include "render/vertex_array.h"

namespace deft {

class RenderCommand {
 public:
  static void ClearColor(const math::Vector4& color);

  static void Clear();

  static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray,
                        unsigned int                        count);

  static void DepthTest(bool flag);

  static void CullFace(bool flag);

  static void Multisample(bool flag);
};

}  // namespace deft

#endif  // __DEFT_RENDER_COMMAND_H__