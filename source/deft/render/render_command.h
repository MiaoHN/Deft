#ifndef __DEFT_RENDER_COMMAND_H__
#define __DEFT_RENDER_COMMAND_H__

#include <memory>

#include "core/math/math.h"
#include "render/render_api.h"
#include "render/vertex_array.h"

namespace deft {

class RenderCommand {
 public:
  static void Init();

  static void ClearColor(const math::Vector4& color);

  static void Clear();

  static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray,
                        unsigned int                        count);

 private:
  static std::unique_ptr<RenderAPI> _api;
};

}  // namespace deft

#endif  // __DEFT_RENDER_COMMAND_H__