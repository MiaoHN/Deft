#include "render/mesh.h"

namespace deft {

Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<float>&         vertices,
             const std::vector<BufferElement>& layouts,
             const std::vector<unsigned int>&  indices) {
  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(vertices);
  _vbo->setElements(layouts);
  _ebo = std::make_shared<IndexBuffer>(indices);
}

Mesh::~Mesh() {}

void Mesh::bind() const {
  _vao->bind();
  _vbo->bind();
  _ebo->bind();
}

void Mesh::unBind() const { _vao->unBind(); }

int Mesh::getCount() const { return _ebo->getCount(); }

std::shared_ptr<Mesh> Mesh::Create(const std::vector<float>&         vertices,
                                     const std::vector<BufferElement>& layouts,
                                     const std::vector<unsigned int>& indices) {
  return std::make_shared<Mesh>(vertices, layouts, indices);
}
}  // namespace deft
