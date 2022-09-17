#ifndef __DEFT_VERTEX_ARRAY_H__
#define __DEFT_VERTEX_ARRAY_H__

#include <memory>

namespace deft {

class VertexArray {
 public:
  virtual ~VertexArray() = default;

  virtual void bind() const   = 0;
  virtual void unBind() const = 0;

  static std::shared_ptr<VertexArray> Create();

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_VERTEX_ARRAY_H__