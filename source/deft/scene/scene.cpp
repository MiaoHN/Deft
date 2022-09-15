#include "scene/scene.h"

#include <glad/glad.h>

#include "app/application.h"
#include "ecs/components/renderable.h"
#include "ecs/components/transform.h"
#include "pch.h"

namespace deft {

Scene::Scene() {
  _registry.init();

  _registry.registerComponent<MeshComponent>();
  _registry.registerComponent<LightDetail>();
  _registry.registerComponent<Transform>();

  _renderSystem = _registry.registerSystem<RenderSystem>();

  Entity    entity = _registry.createEntity();
  Transform transform;
  transform.position = {0.0f, 0.0f, -1.0f};
  MeshComponent meshComponent;
  meshComponent.mesh = Mesh::Create(
      {
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
      },
      {
          {"aPos", ElementType::Float3},
          {"aNormal", ElementType::Float3},
          {"aTexCoord", ElementType::Float2},
      },
      {
          0,  1,  2,  0,  2,  3,   //
          4,  5,  6,  4,  6,  7,   //
          8,  9,  10, 8,  10, 11,  //
          12, 13, 14, 12, 14, 15,  //
          16, 17, 18, 16, 18, 19,  //
          20, 21, 22, 20, 22, 23,  //

      });

  meshComponent.mesh->addTexture(
      Texture::Create("assets/texture/container.jpg"));

  entity.addComponent(meshComponent);
  entity.addComponent(transform);
}

Scene::~Scene() {}

void Scene::updateEditMode(float dt, const std::shared_ptr<Camera>& camera) {
  _renderSystem->updateEditMode(dt, camera);
}

Registry& Scene::getRegistry() { return _registry; }

}  // namespace deft
