#include "platform/render/opengl/opengl_index_buffer.h"

#include <glad/glad.h>

namespace deft {

OpenGLIndexBuffer::OpenGLIndexBuffer() : _id(0) {}

OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<unsigned int> &indices)
    : _id(0), _indices(indices) {}

OpenGLIndexBuffer::OpenGLIndexBuffer(int count) : _id(0) {
  unsigned int index = 0;
  for (int i = 0; i < count; ++i, ++index) {
    _indices.push_back(index);
  }
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  _indices.clear();
  clearEbo();
}

void OpenGLIndexBuffer::addIndices(const std::vector<unsigned int> &indices) {
  unsigned int base = *std::max_element(_indices.begin(), _indices.end()) + 1;
  for (auto &index : indices) {
    _indices.push_back(base + index);
  }
  clearEbo();
}

void OpenGLIndexBuffer::addIndices(int count) {
  unsigned int base = *std::max_element(_indices.begin(), _indices.end()) + 1;
  for (int i = 0; i < count; ++i) {
    _indices.push_back(base);
    ++base;
  }
  clearEbo();
}

int OpenGLIndexBuffer::getCount() const { return _indices.size(); }

void OpenGLIndexBuffer::bind() const {
  if (_id == 0) {
    generateEbo();
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void OpenGLIndexBuffer::unBind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::generateEbo() const {
  glCreateBuffers(1, &_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
               _indices.data(), GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::clearEbo() const {
  if (_id) {
    glDeleteBuffers(1, &_id);
  }
  _id = 0;
}

}  // namespace deft
