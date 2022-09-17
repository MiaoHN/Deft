#include "render/vertex_array.h"

#include "pch.h"
#include "platform/render/opengl/opengl_vertex_array.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<VertexArray> VertexArray::Create() {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLVertexArray>();
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft
