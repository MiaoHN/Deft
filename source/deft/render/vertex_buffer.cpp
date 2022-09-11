#include "render/vertex_buffer.h"

#include <glad/glad.h>

#include "pch.h"

namespace deft {

BufferElement::BufferElement(const std::string& name, ElementType type,
                             bool normalized)
    : name(name), type(type), normalized(normalized) {}

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

VertexBuffer::VertexBuffer(const std::vector<float>& data)
    : _id(0), _data(data) {}

void VertexBuffer::bind() const {
  if (!_id) genVbo();
  glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::unBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

std::vector<float> VertexBuffer::getData() const { return _data; }

void VertexBuffer::setData(const std::vector<float>& data) {
  _data = data;
  clearVbo();
}

void VertexBuffer::setElements(const std::vector<BufferElement>& element) {
  _elements = element;
  clearVbo();
}

void VertexBuffer::genVbo() const {
  glCreateBuffers(1, &_id);
  glBindBuffer(GL_ARRAY_BUFFER, _id);
  glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(float), _data.data(),
               GL_STATIC_DRAW);

  setLayout();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout() const {
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

void VertexBuffer::clearVbo() const {
  if (_id) glDeleteBuffers(1, &_id);
  _id = 0;
}

}  // namespace deft
