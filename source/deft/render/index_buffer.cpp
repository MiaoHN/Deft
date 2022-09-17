#include "render/index_buffer.h"

#include "pch.h"
#include "platform/render/opengl/opengl_index_buffer.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<IndexBuffer> IndexBuffer::Create(
    const std::vector<unsigned int> &indices) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLIndexBuffer>(indices);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(int count) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLIndexBuffer>(count);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft