#ifndef __DEFT_INDEX_BUFFER_H__
#define __DEFT_INDEX_BUFFER_H__

#include <memory>
#include <vector>

namespace deft {

class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  virtual void addIndices(const std::vector<unsigned int> &indices) = 0;
  virtual void addIndices(int count)                                = 0;

  virtual int getCount() const = 0;

  virtual void bind() const   = 0;
  virtual void unBind() const = 0;

  static std::shared_ptr<IndexBuffer> Create(
      const std::vector<unsigned int> &indices);
  static std::shared_ptr<IndexBuffer> Create(int count);
};

}  // namespace deft

#endif  // __DEFT_INDEX_BUFFER_H__
