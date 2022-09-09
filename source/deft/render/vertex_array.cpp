#include "render/vertex_array.h"

#include <glad/glad.h>

#include "pch.h"

namespace deft {

VertexArray::VertexArray() { glCreateVertexArrays(1, &_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_id); }

void VertexArray::bind() const { glBindVertexArray(_id); }

void VertexArray::unBind() const { glBindVertexArray(0); }

}  // namespace deft
