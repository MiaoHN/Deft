#ifndef __DEFT_OPENGL_SHADER_H__
#define __DEFT_OPENGL_SHADER_H__

#include "render/shader.h"

namespace deft {

class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& vertPath, const std::string& fragPath);
  ~OpenGLShader();

  void bind() const override;
  void unBind() const override;

  void setMatrix4(const std::string& name, const math::Matrix4& mat) override;
  void setInt(const std::string& name, int value) override;
  void setFloat(const std::string& name, float value) override;
  void setFloat3(const std::string& name, const math::Vector3& vec) override;

 private:
  static std::vector<char> ReadFile(const std::string& path);

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_SHADER_H__