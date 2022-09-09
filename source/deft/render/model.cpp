#include "render/model.h"

namespace deft {

Model::Model() = default;

Model::Model(const std::vector<float>&        vertices,
             const std::vector<unsigned int>& indices) {
  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(vertices);
  _vbo->setElements({{"aPos", ElementType::Float3}});
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

}  // namespace deft
