#ifndef __DEFT_INDEX_BUFFER_H__
#define __DEFT_INDEX_BUFFER_H__

#include <vector>

namespace deft {

class IndexBuffer {
 public:
  IndexBuffer();
  IndexBuffer(const std::vector<unsigned int> &indices);
  IndexBuffer(int count);
  ~IndexBuffer();

  void addIndices(const std::vector<unsigned int> &indices);
  void addIndices(int count);

  int getCount() const;

  void bind() const;
  void unBind() const;

 private:
  void generateEbo() const;
  void clearEbo() const;

 private:
  mutable unsigned int _id;

  std::vector<unsigned int> _indices;
};

}  // namespace deft

#endif  // __DEFT_INDEX_BUFFER_H__
