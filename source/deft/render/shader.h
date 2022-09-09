#ifndef __DEFT_SHADER_H__
#define __DEFT_SHADER_H__

#include <string>
#include <vector>

#include "math/math.h"

namespace deft {

class Shader {
 public:
  Shader(const std::string& vertPath, const std::string& fragPath);
  ~Shader();

  void bind() const;
  void unBind() const;

  void setMatrix4(const std::string& name, const math::Matrix4& mat);
  void setInt(const std::string& name, int value);

 private:
  static std::vector<char> ReadFile(const std::string& path);

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_SHADER_H__