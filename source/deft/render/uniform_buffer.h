#ifndef __DEFT_UNIFORM_BUFFER_H__
#define __DEFT_UNIFORM_BUFFER_H__

#include <glad/glad.h>

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
  UniformBuffer(unsigned int size, unsigned int binding) {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
  }

  ~UniformBuffer() { glDeleteBuffers(1, &_id); }

  void setData(const void* data, unsigned int size, unsigned int offset = 0) {
    glNamedBufferSubData(_id, offset, size, data);
  }

 private:
  unsigned int _id;
};

class UniformBufferLib {
 public:
  static void Add(const std::string&                    name,
                  const std::shared_ptr<UniformBuffer>& uniformBuffer) {
    _map[name] = uniformBuffer;
  }

  static std::shared_ptr<UniformBuffer>& Get(const std::string& name) {
    return _map[name];
  }

 private:
  static std::unordered_map<std::string, std::shared_ptr<UniformBuffer>> _map;
};

}  // namespace deft

#endif  // __DEFT_UNIFORM_BUFFER_H__