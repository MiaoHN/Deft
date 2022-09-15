#ifndef __DEFT_SHADER_H__
#define __DEFT_SHADER_H__

#include <string>
#include <unordered_map>
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
  void setFloat(const std::string& name, float value);
  void setFloat3(const std::string& name, const math::Vector3& vec);

 private:
  static std::vector<char> ReadFile(const std::string& path);

 private:
  unsigned int _id;
};

class ShaderLib {
 public:
  static void Add(const std::string&             name,
                  const std::shared_ptr<Shader>& shader);

  static std::shared_ptr<Shader>& Get(const std::string& name);

 private:
  static std::unordered_map<std::string, std::shared_ptr<Shader>> _map;
};

}  // namespace deft

#endif  // __DEFT_SHADER_H__