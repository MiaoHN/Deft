#include "platform/render/opengl/opengl_shader.h"

#include <glad/glad.h>

namespace deft {

OpenGLShader::OpenGLShader(const std::string& vertPath,
                           const std::string& fragPath)
    : _id(0) {
  std::vector<char> vertSource = ReadFile(vertPath);
  std::vector<char> fragSource = ReadFile(fragPath);
  if (vertSource.empty() || fragSource.empty()) return;

  const char* vertCode = vertSource.data();
  const char* fragCode = fragSource.data();

  // 创建顶点着色器
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // 将着色器源码附加到着色器对象
  glShaderSource(vertexShader, 1, &vertCode, nullptr);
  glCompileShader(vertexShader);
  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    LOG_CLIENT_ERROR(
        "Shader::Shader Failed compilation for vertex shader! detail:\n%s",
        infoLog);
    glDeleteShader(vertexShader);
    return;
  }

  // 创建片段着色器
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragCode, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    LOG_CLIENT_ERROR(
        "Shader::Shader Failed compilation for fragment shader! detail:\n%s",
        infoLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return;
  }

  // 创建程序对象
  unsigned int shaderProgram = glCreateProgram();
  // 将之前编译的着色器附加到程序对象上
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    LOG_CLIENT_ERROR("Shader::Shader Failed link for program! detail:\n%s",
                     infoLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    return;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  _id = shaderProgram;
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(_id); }

void OpenGLShader::bind() const { glUseProgram(_id); }

void OpenGLShader::unBind() const { glUseProgram(0); }

void OpenGLShader::setMatrix4(const std::string&   name,
                              const math::Matrix4& mat) {
  glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE,
                     mat.ptr());
}

void OpenGLShader::setInt(const std::string& name, int value) {
  glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void OpenGLShader::setFloat(const std::string& name, float value) {
  glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void OpenGLShader::setFloat3(const std::string&   name,
                             const math::Vector3& vec) {
  glUniform3f(glGetUniformLocation(_id, name.c_str()), vec.x, vec.y, vec.z);
}

std::vector<char> OpenGLShader::ReadFile(const std::string& path) {
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    LOG_CLIENT_ERROR("Shader::ReadFile Can't open file '%s'", path.c_str());
    file.close();
    return {};
  }

  size_t size = file.tellg();

  std::vector<char> buffer(size + 1);

  file.seekg(0);
  file.read(buffer.data(), size);
  buffer[size] = '\0';

  return buffer;
}

}  // namespace deft
