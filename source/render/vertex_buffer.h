#ifndef __DEFT_VERTEX_BUFFER_H__
#define __DEFT_VERTEX_BUFFER_H__

#include <string>
#include <vector>

namespace deft {

enum class ElementType {
  Int,
  Float,
  Float2,
  Float3,
  Float4,
};

struct BufferElement {
  std::string name;
  ElementType type;
  bool        normalized;

  BufferElement() = default;
  BufferElement(const std::string& name, ElementType type,
                bool normalized = false);
};

class VertexBuffer {
 public:
  VertexBuffer(const std::vector<float>& data);

  void bind() const;
  void unBind() const;

  std::vector<float> getData() const;

  void setData(const std::vector<float>& data);
  void setElements(const std::vector<BufferElement>& element);

 private:
  void genVbo() const;
  void setLayout() const;
  void clearVbo() const;

 private:
  mutable unsigned int _id;

  std::vector<float>         _data;
  std::vector<BufferElement> _elements;
};

}  // namespace deft

#endif  // __DEFT_VERTEX_BUFFER_H__