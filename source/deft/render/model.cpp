#include "render/model.h"

namespace deft {

Model::Model() = default;

Model::Model(const std::vector<float>&         vertices,
             const std::vector<BufferElement>& layouts,
             const std::vector<unsigned int>&  indices) {
  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(vertices);
  _vbo->setElements(layouts);
  _ebo = std::make_shared<IndexBuffer>(indices);
}

Model::~Model() {}

void Model::bind() const {
  _vao->bind();
  _vbo->bind();
  _ebo->bind();
}

void Model::unBind() const { _vao->unBind(); }

int Model::getCount() const { return _ebo->getCount(); }

std::shared_ptr<Model> Model::Create(const std::vector<float>&         vertices,
                                     const std::vector<BufferElement>& layouts,
                                     const std::vector<unsigned int>& indices) {
  return std::make_shared<Model>(vertices, layouts, indices);
}
}  // namespace deft
