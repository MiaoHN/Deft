#include "render/mesh.h"

#include <glad/glad.h>

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

void Mesh::draw(const TransformComponent&      transform,
                const std::shared_ptr<Shader>& shader, Entity entity) {
  bind();
  shader->bind();
  math::Matrix4 model = math::Matrix4(1.0f);

  model = math::rotate(model, math::radians(transform.rotation.x),
                       math::Vector3(1, 0, 0));
  model = math::rotate(model, math::radians(transform.rotation.y),
                       math::Vector3(0, 1, 0));
  model = math::rotate(model, math::radians(transform.rotation.z),
                       math::Vector3(0, 0, 1));

  model = math::scale(model, transform.scale);

  model = math::translate(model, transform.position);

  shader->setMatrix4("model", model);
  for (int i = 0; i < _textures.size(); ++i) {
    _textures[i]->bind(i);
    shader->setInt("textureDiffuse", i);
  }
  glDrawElements(GL_TRIANGLES, getCount(), GL_UNSIGNED_INT, nullptr);
}

int Mesh::getCount() const { return _ebo->getCount(); }

void Mesh::addTexture(const std::shared_ptr<Texture>& texture) {
  _textures.push_back(texture);
}

std::vector<std::shared_ptr<Texture>>& Mesh::getTextures() { return _textures; }

std::shared_ptr<Mesh> Mesh::Create(const std::vector<float>&         vertices,
                                   const std::vector<BufferElement>& layouts,
                                   const std::vector<unsigned int>&  indices) {
  return std::make_shared<Mesh>(vertices, layouts, indices);
}
}  // namespace deft
