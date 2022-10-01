#ifndef __DEFT_UNIFORM_BUFFER_H__
#define __DEFT_UNIFORM_BUFFER_H__

#include <memory>
#include <string>
#include <unordered_map>

#include "math/math.h"

namespace deft {

struct CameraData {
  math::Matrix4 viewProjection;
  math::Vector3 cameraPosition;
};

class UniformBuffer {
 public:
  virtual ~UniformBuffer() = default;

  virtual void setData(const void* data, unsigned int size,
                       unsigned int offset = 0) = 0;

  static std::shared_ptr<UniformBuffer> Create(unsigned int size,
                                               unsigned int binding);
};

}  // namespace deft

#endif  // __DEFT_UNIFORM_BUFFER_H__