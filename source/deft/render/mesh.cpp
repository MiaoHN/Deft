#include "render/mesh.h"

#include "render/render_command.h"

namespace deft {

Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<float>&         vertices,
           const std::vector<BufferElement>& layouts,
           const std::vector<unsigned int>&  indices) {
  _vao = VertexArray::Create();
  _vbo = VertexBuffer::Create(vertices);
  _vbo->setElements(layouts);
  _ebo = IndexBuffer::Create(indices);
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

  shader->setMatrix4("model", transform.getTransform());
  if (_textures.find(TextureType::Diffuse) != _textures.end()) {
    _textures[TextureType::Diffuse]->bind(0);
    shader->setInt("material.diffuse", 0);
  }
  if (_textures.find(TextureType::Specular) != _textures.end()) {
    _textures[TextureType::Specular]->bind(1);
    shader->setInt("material.specular", 1);
  }
  shader->setFloat("material.shininess", 32);

  RenderCommand::DrawIndex(_vao, getCount());
}

int Mesh::getCount() const { return _ebo->getCount(); }

void Mesh::addTexture(TextureType                     type,
                      const std::shared_ptr<Texture>& texture) {
  _textures[type] = texture;
}

std::unordered_map<TextureType, std::shared_ptr<Texture>>& Mesh::getTextures() {
  return _textures;
}

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
