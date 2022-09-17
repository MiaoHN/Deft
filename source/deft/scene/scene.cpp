#include "scene/scene.h"

#include "core/application.h"
#include "ecs/components/light.h"
#include "ecs/components/mesh.h"
#include "ecs/components/tag.h"
#include "ecs/components/transform.h"
#include "pch.h"

namespace deft {

Scene::Scene() {
  _registry.init();

  _registry.registerComponent<MeshComponent>();
  _registry.registerComponent<TransformComponent>();
  _registry.registerComponent<LightComponent>();
  _registry.registerComponent<TagComponent>();

  _renderSystem = _registry.registerSystem<RenderSystem>();
}

Scene::~Scene() {}

void Scene::updateEditMode(float dt, const std::shared_ptr<Camera>& camera) {
  _renderSystem->updateEditMode(dt, camera);
}

Registry& Scene::getRegistry() { return _registry; }

}  // namespace deft
