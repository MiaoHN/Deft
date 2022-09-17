#include "platform/render/opengl/opengl_vertex_buffer.h"

#include <glad/glad.h>

namespace deft {

unsigned int ElementTypeToGLType(ElementType type) {
  switch (type) {
    case ElementType::Int:
      return GL_INT;
    case ElementType::Float:
    case ElementType::Float2:
    case ElementType::Float3:
    case ElementType::Float4:
      return GL_FLOAT;
  }
  LOG_CLIENT_ERROR("::ElementTypeToGLType UnKnown BufferElement Type");
  exit(-1);
}

int ElementCount(ElementType type) {
  switch (type) {
    case ElementType::Int:
    case ElementType::Float:
      return 1;
    case ElementType::Float2:
      return 2;
    case ElementType::Float3:
      return 3;
    case ElementType::Float4:
      return 4;
  }
  LOG_CLIENT_ERROR("::ElementCount UnKnown BufferElement Type");
  exit(-1);
}

int ElementSize(ElementType type) {
  int count = ElementCount(type);
  switch (type) {
    case ElementType::Int:
      return sizeof(int) * count;
    case ElementType::Float:
    case ElementType::Float2:
    case ElementType::Float3:
    case ElementType::Float4:
      return sizeof(float) * count;
  }
  LOG_CLIENT_ERROR("::ElementSize UnKnown BufferElement Type");
  exit(-1);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& data)
    : _id(0), _data(data) {}

void OpenGLVertexBuffer::bind() const {
  if (!_id) genVbo();
  glBindBuffer(GL_ARRAY_BUFFER, _id);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &_id); }

void OpenGLVertexBuffer::unBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

std::vector<float> OpenGLVertexBuffer::getData() const { return _data; }

void OpenGLVertexBuffer::setData(const std::vector<float>& data) {
  _data = data;
  clearVbo();
}

void OpenGLVertexBuffer::setElements(
    const std::vector<BufferElement>& element) {
  _elements = element;
  clearVbo();
}

void OpenGLVertexBuffer::genVbo() const {
  glCreateBuffers(1, &_id);
  glBindBuffer(GL_ARRAY_BUFFER, _id);
  glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(float), _data.data(),
               GL_STATIC_DRAW);

  setLayout();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::setLayout() const {
  int stride = 0;
  for (auto& element : _elements) {
    stride += ElementSize(element.type);
  }

  unsigned int index  = 0;
  int          offset = 0;
  for (auto& element : _elements) {
    glVertexAttribPointer(index, ElementCount(element.type),
                          ElementTypeToGLType(element.type), element.normalized,
                          stride, (const void*)(intptr_t)offset);
    offset += ElementSize(element.type);
    glEnableVertexAttribArray(index);
    ++index;
  }
}

void OpenGLVertexBuffer::clearVbo() const {
  if (_id) glDeleteBuffers(1, &_id);
  _id = 0;
}

}  // namespace deft
