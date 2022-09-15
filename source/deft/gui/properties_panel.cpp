#include "gui/properties_panel.h"

#include <imgui.h>

#include "app/application.h"
#include "ecs/components/mesh.h"
#include "ecs/components/transform.h"

namespace deft {

PropertiesPanel::PropertiesPanel() {}

PropertiesPanel::~PropertiesPanel() {}

void PropertiesPanel::update(
    const std::shared_ptr<HierarchyPanel>& hierarchyPanel) {
  ImGui::Begin("Properties");

  // 显示场景总体信息
  showSceneDetail();

  if (hierarchyPanel->haveSelectedEntity()) {
    Entity entity = hierarchyPanel->getSelectedEntity();

    // 显示位置信息
    showTransform(entity);

    // 显示材质信息
    showMesh(entity);
  }
  ImGui::End();
}

void PropertiesPanel::showSceneDetail() {
  if (ImGui::TreeNode("Scene Detail")) {
    ImGui::Text("Scene fps: %d", Application::Get().getFps());
    ImGui::TreePop();
  }
}

void PropertiesPanel::showTransform(Entity entity) {
  auto& transform = Application::Get()
                        .getScene()
                        ->getRegistry()
                        .getComponent<TransformComponent>(entity);
  if (ImGui::TreeNode("Transform")) {
    ImGui::SliderFloat3("Position", &transform.position.x, -10, 10);
    ImGui::SliderFloat3("Rotation", &transform.rotation.x, 0, 180);
    ImGui::SliderFloat3("Scale", &transform.scale.x, 0.1, 10);
    ImGui::TreePop();
  }
}

void PropertiesPanel::showMesh(Entity entity) {
  if (Application::Get().getScene()->getRegistry().haveComponent<MeshComponent>(
          entity)) {
    auto& meshComponent = Application::Get()
                              .getScene()
                              ->getRegistry()
                              .getComponent<MeshComponent>(entity);
    if (ImGui::TreeNode("Mesh")) {
      auto& textures = meshComponent.mesh->getTextures();
      for (auto& texture : textures) {
        unsigned int textureId = texture->getId();
        ImGui::Image(reinterpret_cast<void*>(textureId), ImVec2{80.0f, 80.0f},
                     ImVec2{0, 1}, ImVec2{1, 0});
        if (texture->getDataType() == Texture::Color) {
          math::Vector3 colorPrev = texture->getColor();
          math::Vector3 color     = texture->getColor();
          if (ImGui::ColorEdit3("color", &color.x)) {
            texture->setColor(color);
          }
        }
        ImGui::Separator();
      }
      ImGui::TreePop();
    }
  }
}

}  // namespace deft
