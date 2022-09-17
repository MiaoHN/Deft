#ifndef __DEFT_OPENGL_RENDER_API_H__
#define __DEFT_OPENGL_RENDER_API_H__

#include "render/render_api.h"

namespace deft {

class OpenGLRenderAPI : public RenderAPI {
 public:
  void init() override;

  void setViewPort(int x, int y, int width, int height) override;

  void clear() override;

  void clearColor(const math::Vector4& color) override;

  void drawIndex(const std::shared_ptr<VertexArray>& vao,
                 unsigned int                        count) override;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_RENDER_API_H__