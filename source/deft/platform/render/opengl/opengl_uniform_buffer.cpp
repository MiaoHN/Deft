#include "platform/render/opengl/opengl_uniform_buffer.h"

#include <glad/glad.h>

namespace deft {

OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int size,
                                         unsigned int binding) {
  glCreateBuffers(1, &_id);
  glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer() { glDeleteBuffers(1, &_id); }

void OpenGLUniformBuffer::setData(const void* data, unsigned int size,
                                  unsigned int offset) {
  glNamedBufferSubData(_id, offset, size, data);
}

}  // namespace deft
