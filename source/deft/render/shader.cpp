#include "render/shader.h"

#include <memory>

#include "core/library/library.h"
#include "pch.h"
#include "platform/render/opengl/opengl_shader.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<Shader> Shader::Create(const std::string& vertPath,
                                       const std::string& fragPath) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLShader>(vertPath, fragPath);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

template <>
std::shared_ptr<Library<Shader>> Library<Shader>::GetInstance() {
  static std::shared_ptr<Library<Shader>> s_instance = nullptr;
  if (s_instance == nullptr) {
    s_instance = std::make_shared<Library<Shader>>();

    s_instance->_map["default"] = Shader::Create("assets/shader/default.vert",
                                                 "assets/shader/default.frag");
  }
  return s_instance;
}

}  // namespace deft
