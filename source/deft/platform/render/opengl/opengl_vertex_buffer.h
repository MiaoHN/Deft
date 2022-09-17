#ifndef __DEFT_OPENGL_VERTEX_BUFFER_H__
#define __DEFT_OPENGL_VERTEX_BUFFER_H__

#include "render/vertex_buffer.h"

namespace deft {

class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(const std::vector<float>& data);
  ~OpenGLVertexBuffer();

  void bind() const override;
  void unBind() const override;

  std::vector<float> getData() const override;

  void setData(const std::vector<float>& data) override;
  void setElements(const std::vector<BufferElement>& element) override;

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

#endif  // __DEFT_OPENGL_VERTEX_BUFFER_H__