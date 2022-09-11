#include "render/renderer.h"

#include <glad/glad.h>

namespace deft {

Renderer::Renderer() {
  _frameModel = Mesh::Create(
      {
          -1.0f, -1.0f, 0.0f, 0.0f,  //
          1.0f, -1.0f, 1.0f, 0.0f,   //
          1.0f, 1.0f, 1.0f, 1.0f,    //
          -1.0f, 1.0f, 0.0f, 1.0f,   //
      },
      {
          {"aPos", ElementType::Float2},
          {"aTexCoord", ElementType::Float2},
      },
      {
          0, 1, 2, 0, 2, 3,  //
      });

  _frameShader = std::make_shared<Shader>("assets/shader/frame_buffer.vert",
                                          "assets/shader/frame_buffer.frag");
  _frameShader->bind();
  _frameShader->setInt("colorTexture", 0);
}

Renderer::~Renderer() {}

void Renderer::begin(std::shared_ptr<Camera> camera) {
  _proj = camera->getProjection();
  _view = camera->getView();
}

void Renderer::drawFrame(std::shared_ptr<FrameBuffer>& frameBuffer) {
  _frameModel->bind();
  _frameShader->bind();
  glBindTexture(GL_TEXTURE_2D, frameBuffer->getColorAttachment());
  glDrawElements(GL_TRIANGLES, _frameModel->getCount(), GL_UNSIGNED_INT,
                 nullptr);
}

void Renderer::submit(const std::shared_ptr<Model>&  model,
                      const std::shared_ptr<Shader>& shader,
                      const math::Vector3&           position) {
  auto& mesh     = model->getMesh();
  auto& textures = model->getTextures();

  mesh->bind();
  shader->bind();
  for (int i = 0; i < textures.size(); ++i) {
    shader->setInt("diffuseTexture", i);
    textures[i]->bind(i);
  }
  auto modelMatrix = math::translate(math::Matrix4(1.0f), position);
  shader->setMatrix4("transform", _proj * _view * modelMatrix);

  glDrawElements(GL_TRIANGLES, mesh->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::submit(const std::shared_ptr<Mesh>&    mesh,
                      const std::shared_ptr<Shader>&  shader,
                      const std::shared_ptr<Texture>& texture,
                      const math::Vector3&            position) {
  mesh->bind();
  shader->bind();
  shader->setInt("diffuseTexture", 0);
  texture->bind();
  auto modelMatrix = math::translate(math::Matrix4(1.0f), position);
  shader->setMatrix4("transform", _proj * _view * modelMatrix);

  glDrawElements(GL_TRIANGLES, mesh->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::end() {}

}  // namespace deft
