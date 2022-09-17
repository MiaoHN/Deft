#ifndef __DEFT_OPENGL_INDEX_BUFFER_H__
#define __DEFT_OPENGL_INDEX_BUFFER_H__

#include "render/index_buffer.h"

namespace deft {

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer();
  OpenGLIndexBuffer(const std::vector<unsigned int> &indices);
  OpenGLIndexBuffer(int count);
  ~OpenGLIndexBuffer();

  void addIndices(const std::vector<unsigned int> &indices) override;
  void addIndices(int count) override;

  int getCount() const override;

  void bind() const override;
  void unBind() const override;

 private:
  void generateEbo() const;
  void clearEbo() const;

 private:
  mutable unsigned int _id;

  std::vector<unsigned int> _indices;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_INDEX_BUFFER_H__