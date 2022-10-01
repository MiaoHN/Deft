#include "render/uniform_buffer.h"

#include "library/library.h"
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

template <>
std::shared_ptr<Library<UniformBuffer>> Library<UniformBuffer>::GetInstance() {
  static std::shared_ptr<Library<UniformBuffer>> s_instance = nullptr;
  if (s_instance == nullptr) {
    s_instance = std::make_shared<Library<UniformBuffer>>();

    s_instance->_map["cameraUniform"] =
        UniformBuffer::Create(sizeof(CameraData), 0);
  }
  return s_instance;
}

}  // namespace deft
