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
  virtual ~VertexBuffer() = default;

  virtual void bind() const   = 0;
  virtual void unBind() const = 0;

  virtual std::vector<float> getData() const = 0;

  virtual void setData(const std::vector<float>& data)                = 0;
  virtual void setElements(const std::vector<BufferElement>& element) = 0;

  static std::shared_ptr<VertexBuffer> Create(const std::vector<float>& data);
};

}  // namespace deft

#endif  // __DEFT_VERTEX_BUFFER_H__