#ifndef __DEFT_RENDER_SYSTEM_H__
#define __DEFT_RENDER_SYSTEM_H__

#include "ecs/ecs.h"
#include "render/camera.h"
#include "render/renderer.h"
#include "render/shader.h"

namespace deft {

class RenderSystem : public System {
 public:
  RenderSystem() {}

  void updateEditMode(float                          dt,
                      const std::shared_ptr<Camera>& camera) override {
    std::vector<Entity>& entities = _handled->getEntiesUsed();

    Renderer::Begin(camera);

    for (auto& entity : entities) {
      if (entity.haveComponent<MeshComponent>()) {
        Transform&     transform     = entity.getComponent<Transform>();
        MeshComponent& meshComponent = entity.getComponent<MeshComponent>();

        Renderer::Submit(transform, meshComponent, ShaderLib::Get("default"),
                         entity);
      }
    }

    Renderer::End();
  }
};

}  // namespace deft

#endif  // __DEFT_RENDER_SYSTEM_H__