#include "render/model.h"

namespace deft {

Model::Model(const std::shared_ptr<Mesh>&    mesh,
             const std::shared_ptr<Texture>& texture) {
  _mesh = mesh;
  _textures.push_back(texture);
}

Model::~Model() {}

std::shared_ptr<Mesh>& Model::getMesh() { return _mesh; }

std::vector<std::shared_ptr<Texture>>& Model::getTextures() {
  return _textures;
}

std::shared_ptr<Model> Model::Create(const std::shared_ptr<Mesh>&    mesh,
                                     const std::shared_ptr<Texture>& texture) {
  return std::make_shared<Model>(mesh, texture);
}

}  // namespace deft
