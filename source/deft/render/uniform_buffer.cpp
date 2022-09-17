#include "render/uniform_buffer.h"

#include "platform/render/opengl/opengl_uniform_buffer.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<UniformBuffer> UniformBuffer::Create(unsigned int size,
                                                     unsigned int binding) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLUniformBuffer>(size, binding);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

std::unordered_map<std::string, std::shared_ptr<UniformBuffer>>
    UniformBufferLib::_map;

}  // namespace deft
