#include "render/render_api.h"

#include "platform/render/opengl/opengl_render_api.h"

namespace deft {

RenderAPI::API RenderAPI::_api = API::OpenGL;

std::unique_ptr<RenderAPI> RenderAPI::Create() {
  switch (_api) {
    case RenderAPI::OpenGL:
      return std::make_unique<OpenGLRenderAPI>();
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft
