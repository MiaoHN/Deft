#include "render/renderer.h"

#include "ecs/components/component.h"
#include "core/library/library.h"
#include "render/render_command.h"
#include "render/uniform_buffer.h"

namespace deft {

void Renderer::Init() { RenderCommand::Init(); }

void Renderer::Begin(std::shared_ptr<Camera> camera) {
  auto cameraUniform =
      Library<UniformBuffer>::GetInstance()->get("cameraUniform");

  auto projection = camera->getProjection();
  auto view       = camera->getView();

  CameraData cameraData;
  cameraData.cameraPosition = camera->getPosition();
  cameraData.viewProjection = projection * view;

  cameraUniform->setData(&cameraData, sizeof(cameraData));
}

void Renderer::Submit(const TransformComponent&      transform,
                      const MeshComponent&           meshComponent,
                      const std::shared_ptr<Shader>& shader,
                      const Entity&                  entity) {
  meshComponent.mesh->draw(transform, shader, entity);
}

void Renderer::End() {}

}  // namespace deft
