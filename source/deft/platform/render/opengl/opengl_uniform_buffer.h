#ifndef __DEFT_OPENGL_UNIFORM_BUFFER_H__
#define __DEFT_OPENGL_UNIFORM_BUFFER_H__

#include "render/uniform_buffer.h"

namespace deft {

class OpenGLUniformBuffer : public UniformBuffer {
 public:
  OpenGLUniformBuffer(unsigned int size, unsigned int binding);
  ~OpenGLUniformBuffer();

  void setData(const void* data, unsigned int size,
               unsigned int offset = 0) override;

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_UNIFORM_BUFFER_H__