#include "render/vertex_buffer.h"

#include "pch.h"
#include "platform/render/opengl/opengl_vertex_buffer.h"
#include "render/render_api.h"

namespace deft {

BufferElement::BufferElement(const std::string& name, ElementType type,
                             bool normalized)
    : name(name), type(type), normalized(normalized) {}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(
    const std::vector<float>& data) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLVertexBuffer>(data);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}
}  // namespace deft
