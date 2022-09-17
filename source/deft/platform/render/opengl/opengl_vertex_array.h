#ifndef __DEFT_OPENGL_VERTEX_ARRAY_H__
#define __DEFT_OPENGL_VERTEX_ARRAY_H__

#include <glad/glad.h>

#include "render/vertex_array.h"

namespace deft {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray();

  void bind() const override;
  void unBind() const override;

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_VERTEX_ARRAY_H__