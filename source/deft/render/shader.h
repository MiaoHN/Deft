#ifndef __DEFT_SHADER_H__
#define __DEFT_SHADER_H__

#include <string>
#include <unordered_map>
#include <vector>

#include "core/math/math.h"

namespace deft {

class Shader {
 public:
  virtual ~Shader() = default;

  virtual void bind() const   = 0;
  virtual void unBind() const = 0;

  virtual void setMatrix4(const std::string&   name,
                          const math::Matrix4& mat)                         = 0;
  virtual void setInt(const std::string& name, int value)                   = 0;
  virtual void setFloat(const std::string& name, float value)               = 0;
  virtual void setFloat3(const std::string& name, const math::Vector3& vec) = 0;

  static std::shared_ptr<Shader> Create(const std::string& vertPath,
                                        const std::string& fragPath);
};

}  // namespace deft

#endif  // __DEFT_SHADER_H__