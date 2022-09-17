#include "render/graphic_context.h"

#include "pch.h"
#include "platform/render/opengl/opengl_graphic_context.h"
#include "render/render_api.h"

namespace deft {

std::unique_ptr<GraphicContext> GraphicContext::Create(void* handler) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_unique<OpenGLGraphicContext>(handler);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft
