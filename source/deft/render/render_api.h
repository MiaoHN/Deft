#ifndef __DEFT_RENDER_API_H__
#define __DEFT_RENDER_API_H__

#include <memory>

#include "math/math.h"
#include "render/vertex_array.h"

namespace deft {

class RenderAPI {
 public:
  enum API {
    UnKnown,
    OpenGL,
  };

  virtual void init() = 0;

  virtual void setViewPort(int x, int y, int width, int height) = 0;

  virtual void clear() = 0;

  virtual void clearColor(const math::Vector4& color) = 0;

  virtual void drawIndex(const std::shared_ptr<VertexArray>& vao,
                         unsigned int                        count) = 0;

  static void Set(API api) { _api = api; }
  static API  Get() { return _api; }

  static std::unique_ptr<RenderAPI> Create();

 private:
  static API _api;
};

}  // namespace deft

#endif  // __DEFT_RENDER_API_H__