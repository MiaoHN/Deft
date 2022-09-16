#include "render/mesh.h"

#include "render/render_command.h"

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
    switch (_textures[i]->getType()) {
      case TextureType::Diffuse: {
        shader->setInt("material.diffuse", i);
        break;
      }
      case TextureType::Specular: {
        shader->setInt("material.specular", i);
        break;
      }
    }
  }
  shader->setFloat("material.shininess", 32);

  RenderCommand::DrawIndex(_vao, getCount());
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

std::shared_ptr<Mesh> Mesh::Cube() {
  static std::vector<float> vertices = {
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 前
      0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 前
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 前
      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 前

      0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  // 后
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,  // 后
      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  // 后
      0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,  // 后

      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // 左
      -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // 左
      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,  // 左
      -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // 左

      0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 右
      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 右
      0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 右
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 右

      -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // 上
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 上
      0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // 上
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 上

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  // 下
      0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  // 下
      0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,  // 下
      -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  // 下
  };

  static std::vector<BufferElement> layout = {
      {"aPos", ElementType::Float3},
      {"aNormal", ElementType::Float3},
      {"aTexCoord", ElementType::Float2},
  };

  static std::vector<unsigned int> indices = {
      0,  1,  2,  0,  2,  3,   //
      4,  5,  6,  4,  6,  7,   //
      8,  9,  10, 8,  10, 11,  //
      12, 13, 14, 12, 14, 15,  //
      16, 17, 18, 16, 18, 19,  //
      20, 21, 22, 20, 22, 23,  //
  };
  return Create(vertices, layout, indices);
}

}  // namespace deft
