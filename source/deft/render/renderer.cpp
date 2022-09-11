#include "render/renderer.h"

#include <glad/glad.h>

#include "components/component.h"

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
  _proj      = camera->getProjection();
  _view      = camera->getView();
  _cameraPos = camera->getPosition();
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
  shader->setMatrix4("model", modelMatrix);
  shader->setFloat3("objectColor", model->getTextures()[0]->getColor());
  shader->setFloat3("viewPos", _cameraPos);
  // shader->setFloat3("material.ambient", );
  for (auto& lightId : _lights) {
    auto& lightData = g_registry.getComponent<LightDetail>(lightId);
    auto& transform = g_registry.getComponent<Transform>(lightId);
    shader->setFloat3("lightColor", lightData.ambient);
    shader->setFloat3("lightPos", transform.position);
  }

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
  shader->setMatrix4("model", modelMatrix);
  shader->setFloat3("objectColor", {0.2f, 0.4f, 0.7f});
  shader->setFloat3("viewPos", _cameraPos);
  for (auto& lightId : _lights) {
    auto& lightData = g_registry.getComponent<LightDetail>(lightId);
    auto& transform = g_registry.getComponent<Transform>(lightId);
    shader->setFloat3("lightColor", lightData.ambient);
    shader->setFloat3("lightPos", transform.position);
  }

  glDrawElements(GL_TRIANGLES, mesh->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::submit(const std::shared_ptr<SceneObject>& object,
                      const std::shared_ptr<Shader>&      shader,
                      const math::Vector3&                position) {
  auto& model    = object->getModel();
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
  shader->setMatrix4("model", modelMatrix);
  shader->setFloat3("objectColor", model->getTextures()[0]->getColor());
  shader->setFloat3("viewPos", _cameraPos);
  auto material = g_registry.getComponent<MaterialComp>(object->getEntityId());
  shader->setFloat3("material.ambient", material.ambient);
  shader->setFloat3("material.diffuse", material.diffuse);
  shader->setFloat3("material.specular", material.specular);
  shader->setFloat("material.shininess", material.shininess);
  for (auto& lightId : _lights) {
    auto& lightData = g_registry.getComponent<LightDetail>(lightId);
    auto& transform = g_registry.getComponent<Transform>(lightId);
    shader->setFloat3("light.ambient", lightData.ambient);
    shader->setFloat3("light.diffuse", lightData.diffuse);
    shader->setFloat3("light.specular", lightData.specular);
    shader->setFloat3("lightPos", transform.position);
  }

  glDrawElements(GL_TRIANGLES, mesh->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::submit(const std::shared_ptr<SceneObject>& object,
                      const std::shared_ptr<Shader>&      shader,
                      const std::shared_ptr<Texture>&     texture,
                      const math::Vector3&                position) {
  auto& model = object->getModel();
  auto& mesh  = model->getMesh();
  mesh->bind();
  shader->bind();
  shader->setInt("diffuseTexture", 0);
  texture->bind();
  auto modelMatrix = math::translate(math::Matrix4(1.0f), position);
  shader->setMatrix4("transform", _proj * _view * modelMatrix);
  shader->setMatrix4("model", modelMatrix);
  shader->setFloat3("objectColor", {0.2f, 0.4f, 0.7f});
  shader->setFloat3("viewPos", _cameraPos);
  auto material = g_registry.getComponent<MaterialComp>(object->getEntityId());
  shader->setFloat3("material.ambient", material.ambient);
  shader->setFloat3("material.diffuse", material.diffuse);
  shader->setFloat3("material.specular", material.specular);
  shader->setFloat("material.shininess", material.shininess);
  for (auto& lightId : _lights) {
    auto& lightData = g_registry.getComponent<LightDetail>(lightId);
    auto& transform = g_registry.getComponent<Transform>(lightId);
    shader->setFloat3("light.ambient", lightData.ambient);
    shader->setFloat3("light.diffuse", lightData.diffuse);
    shader->setFloat3("light.specular", lightData.specular);
    shader->setFloat3("lightPos", transform.position);
  }

  glDrawElements(GL_TRIANGLES, mesh->getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::addLight(Entity entity) { _lights.push_back(entity); }

void Renderer::end() { _lights.clear(); }

}  // namespace deft
