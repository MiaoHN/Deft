#include "render/renderer.h"

#include <glad/glad.h>

namespace deft {

void Renderer::begin(std::shared_ptr<Camera> camera) {
  _proj = camera->getProjection();
  _view = camera->getView();
}

void Renderer::submit(const std::shared_ptr<Model> &  model,
                      const std::shared_ptr<Shader> & shader,
                      const std::shared_ptr<Texture> &texture,
                      const math::Vector3 &           position) {
  model->bind();
  shader->bind();
  texture->bind();
  auto modelMatrix = math::translate(math::Matrix4(1.0f), position);
  shader->setMatrix4("transform", _proj * _view * modelMatrix);

  glDrawElements(GL_TRIANGLES, model->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::end() {}

}  // namespace deft
