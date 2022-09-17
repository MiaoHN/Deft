#include "platform/render/opengl/opengl_vertex_array.h"

namespace deft {

OpenGLVertexArray::OpenGLVertexArray() { glCreateVertexArrays(1, &_id); }

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &_id); }

void OpenGLVertexArray::bind() const { glBindVertexArray(_id); }

void OpenGLVertexArray::unBind() const { glBindVertexArray(0); }

}  // namespace deft
