#include "gui/properties_panel.h"

#include <imgui.h>

#include "app/application.h"
#include "ecs/components/renderable.h"
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

    // 显示物体光照属性
    // showMaterial(entity);

    // 显示光源属性
    // showLight(entity);
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
  auto& transform =
      Application::Get().getScene()->getRegistry().getComponent<Transform>(
          entity);
  if (ImGui::TreeNode("Transform")) {
    ImGui::InputFloat3("Position", &transform.position.x);
    // ImGui::SliderFloat3("Position", &transform.position.x, -5.0f, 5.0f);
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
      }
      ImGui::TreePop();
    }
  }
}

void PropertiesPanel::showMaterial(Entity entity) {
  if (Application::Get().getScene()->getRegistry().haveComponent<MaterialComp>(
          entity)) {
    if (ImGui::TreeNode("Material")) {
      auto& material = Application::Get()
                           .getScene()
                           ->getRegistry()
                           .getComponent<MaterialComp>(entity);
      ImGui::ColorEdit3("ambient", &material.ambient.x);
      ImGui::ColorEdit3("diffuse", &material.diffuse.x);
      ImGui::ColorEdit3("specular", &material.specular.x);
      ImGui::DragFloat("shininess", &material.shininess);
      ImGui::TreePop();
    }
  }
}

void PropertiesPanel::showLight(Entity entity) {
  if (Application::Get().getScene()->getRegistry().haveComponent<LightDetail>(
          entity)) {
    if (ImGui::TreeNode("Light")) {
      auto& lightDetail = Application::Get()
                              .getScene()
                              ->getRegistry()
                              .getComponent<LightDetail>(entity);
      ImGui::ColorEdit3("ambient", &lightDetail.ambient.x);
      ImGui::ColorEdit3("diffuse", &lightDetail.diffuse.x);
      ImGui::ColorEdit3("specular", &lightDetail.specular.x);
      ImGui::TreePop();
    }
  }
}

}  // namespace deft
