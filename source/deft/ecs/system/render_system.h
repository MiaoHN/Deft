#ifndef __DEFT_RENDER_SYSTEM_H__
#define __DEFT_RENDER_SYSTEM_H__

#include "ecs/components/light.h"
#include "ecs/ecs.h"
#include "library/library.h"
#include "render/camera.h"
#include "render/render_command.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/texture.h"
#include "render/uniform_buffer.h"

namespace deft {

class RenderSystem : public System {
 public:
  RenderSystem() {}

  void updateEditMode(float                          dt,
                      const std::shared_ptr<Camera>& camera) override {
    std::vector<Entity>& entities = _handled->getEntiesUsed();

    Renderer::Begin(camera);

    auto shader = Library<Shader>::GetInstance()->get("default");

    lightConfigurate(shader);

    for (auto& entity : entities) {
      if (entity.haveComponent<MeshComponent>()) {
        auto& transform     = entity.getComponent<TransformComponent>();
        auto& meshComponent = entity.getComponent<MeshComponent>();

        Renderer::Submit(transform, meshComponent, shader, entity);
      }
    }

    Renderer::End();
  }

 private:
  void lightConfigurate(const std::shared_ptr<Shader>& shader) {
    std::vector<Entity>& entities = _handled->getEntiesUsed();

    shader->bind();

    int directionLightCount = 0;
    int pointLightCount     = 0;
    int spotLightCount      = 0;
    for (auto& entity : entities) {
      if (entity.haveComponent<LightComponent>()) {
        auto& light = entity.getComponent<LightComponent>();
        switch (light.type) {
          case LightType::Direction: {
            std::string name =
                "directionLights[" + std::to_string(directionLightCount) + "].";
            shader->setFloat3(name + "direction", light.direction);
            shader->setFloat3(name + "ambient", light.ambient);
            shader->setFloat3(name + "diffuse", light.diffuse);
            shader->setFloat3(name + "specular", light.specular);
            ++directionLightCount;
            break;
          }
          case LightType::Point: {
            auto& transform = entity.getComponent<TransformComponent>();

            std::string name =
                "pointLights[" + std::to_string(pointLightCount) + "].";
            shader->setFloat3(name + "position", transform.position);
            shader->setFloat(name + "constant", light.constant);
            shader->setFloat(name + "linear", light.linear);
            shader->setFloat(name + "quadratic", light.quadratic);
            shader->setFloat3(name + "ambient", light.ambient);
            shader->setFloat3(name + "diffuse", light.diffuse);
            shader->setFloat3(name + "specular", light.specular);
            ++pointLightCount;
            break;
          }
          case LightType::Spot: {
            auto& transform = entity.getComponent<TransformComponent>();

            std::string name =
                "spotLights[" + std::to_string(spotLightCount) + "].";
            shader->setFloat3(name + "position", transform.position);
            shader->setFloat3(name + "direction", light.direction);
            shader->setFloat(name + "cutOff", light.cutOff);
            shader->setFloat(name + "outerCutOff", light.outerCutOff);
            shader->setFloat(name + "constant", light.constant);
            shader->setFloat(name + "linear", light.linear);
            shader->setFloat(name + "quadratic", light.quadratic);
            shader->setFloat3(name + "ambient", light.ambient);
            shader->setFloat3(name + "diffuse", light.diffuse);
            shader->setFloat3(name + "specular", light.specular);
            ++spotLightCount;
            break;
          }
        }
      }
    }

    shader->setInt("directionLightCount", directionLightCount);
    shader->setInt("pointLightCount", pointLightCount);
    shader->setInt("spotLightCount", spotLightCount);
  }
};

}  // namespace deft

#endif  // __DEFT_RENDER_SYSTEM_H__