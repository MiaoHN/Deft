#include "scene/scene.h"

#include <glad/glad.h>

#include "app/application.h"
#include "ecs/components/light.h"
#include "ecs/components/mesh.h"
#include "ecs/components/transform.h"
#include "pch.h"

namespace deft {

Scene::Scene() {
  _registry.init();

  _registry.registerComponent<MeshComponent>();
  _registry.registerComponent<TransformComponent>();
  _registry.registerComponent<LightComponent>();

  _renderSystem = _registry.registerSystem<RenderSystem>();

  Entity box1 = _registry.createEntity("Box1");
  Entity box2 = _registry.createEntity("Box2");

  TransformComponent transform;
  transform.position = {0.0f, 0.0f, 0.0f};
  transform.scale    = {1.0f, 1.0f, 1.0f};
  transform.rotation = {0.0f, 0.0f, 0.0f};
  box1.addComponent(transform);
  transform.position = {2.0f, 1.0f, -1.5f};
  transform.scale    = {1.0f, 1.0f, 1.0f};
  transform.rotation = {0.0f, 0.0f, 0.0f};
  box2.addComponent(transform);

  MeshComponent meshComponent;
  meshComponent.mesh = Mesh::Cube();

  meshComponent.mesh->addTexture(
      Texture::Create("assets/texture/container.jpg", TextureType::Diffuse));
  meshComponent.mesh->addTexture(
      Texture::Create(math::Vector3(1.0f, 1.0f, 1.0f), TextureType::Specular));
  box1.addComponent(meshComponent);
  box2.addComponent(meshComponent);

  Entity directionLight = _registry.createEntity("Direction Light");

  LightComponent lightComponent;
  lightComponent.type      = LightType::Direction;
  lightComponent.direction = math::Vector3(-1.0f, -1.0f, -1.0f);
  lightComponent.ambient   = math::Vector3(0.05f, 0.05f, 0.05f);
  lightComponent.diffuse   = math::Vector3(0.4f, 0.4f, 0.4f);
  lightComponent.specular  = math::Vector3(0.5f, 0.5f, 0.5f);

  directionLight.addComponent(lightComponent);

  Entity pointLight        = _registry.createEntity("Point Light");
  lightComponent.type      = LightType::Point;
  lightComponent.ambient   = math::Vector3(0.05f, 0.05f, 0.05f);
  lightComponent.diffuse   = math::Vector3(0.8f, 0.8f, 0.8f);
  lightComponent.specular  = math::Vector3(1.0f, 1.0f, 1.0f);
  lightComponent.constant  = 1.0f;
  lightComponent.linear    = 0.09f;
  lightComponent.quadratic = 0.032f;

  pointLight.addComponent(lightComponent);
  transform.position = math::Vector3(-2.0f, -4.0f, 3.0f);
  transform.rotation = math::Vector3(0.0f, 0.0f, 0.0f);
  transform.scale    = math::Vector3(0.2f, 0.2f, 0.2f);

  pointLight.addComponent(transform);
  MeshComponent pointLightMeshComponent;
  pointLightMeshComponent.mesh = Mesh::Cube();
  pointLightMeshComponent.mesh->addTexture(
      Texture::Create(math::Vector3(1.0f, 1.0f, 1.0f), TextureType::Diffuse));
  pointLight.addComponent(pointLightMeshComponent);
}

Scene::~Scene() {}

void Scene::updateEditMode(float dt, const std::shared_ptr<Camera>& camera) {
  _renderSystem->updateEditMode(dt, camera);
}

Registry& Scene::getRegistry() { return _registry; }

}  // namespace deft
