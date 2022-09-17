#include "render/shader.h"

#include "pch.h"
#include "platform/render/opengl/opengl_shader.h"
#include "render/render_api.h"

namespace deft {

std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderLib::_map;

void ShaderLib::Add(const std::string&             name,
                    const std::shared_ptr<Shader>& shader) {
  if (_map.find(name) != _map.end()) return;
  _map[name] = shader;
}

std::shared_ptr<Shader>& ShaderLib::Get(const std::string& name) {
  return _map[name];
}

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

}  // namespace deft
