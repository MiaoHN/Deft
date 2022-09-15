#include "gui/properties_panel.h"

#include <imgui.h>

#include "app/application.h"
#include "ecs/components/mesh.h"
#include "ecs/components/transform.h"
#include "pch.h"

namespace deft {

PropertiesPanel::PropertiesPanel() {}

PropertiesPanel::~PropertiesPanel() {}

void PropertiesPanel::update(
    const std::shared_ptr<HierarchyPanel>& hierarchyPanel) {
  ImGui::Begin("Properties");

  if (hierarchyPanel->haveSelectedEntity()) {
    Entity* entity = hierarchyPanel->getSelectedEntity();

    ImGui::LabelText("Entity Name", entity->getName().c_str());

    char buf[128] = "";
    if (ImGui::InputText("Rename", buf, 128)) {
      std::string newName = std::string(buf, strlen(buf));
      entity->setName(newName);
    }

    // if (ImGui::Button("Add Component")) {
    // }

    // 显示位置信息
    showTransform(*entity);

    // 显示材质信息
    showMesh(*entity);

    // 显示光照信息
    showLight(*entity);
  }
  ImGui::End();
}

void PropertiesPanel::showTransform(Entity entity) {
  if (Application::Get()
          .getScene()
          ->getRegistry()
          .haveComponent<TransformComponent>(entity)) {
    auto& transform = Application::Get()
                          .getScene()
                          ->getRegistry()
                          .getComponent<TransformComponent>(entity);
    if (ImGui::TreeNode("Transform")) {
      ImGui::DragFloat3("Position", &transform.position.x);
      ImGui::DragFloat3("Rotation", &transform.rotation.x);
      ImGui::DragFloat3("Scale", &transform.scale.x);
      ImGui::TreePop();
    }
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
        switch (texture->getType()) {
          case TextureType::Diffuse:
            ImGui::Text("Diffuse");
            break;
          case TextureType::Specular:
            ImGui::Text("Specular");
            break;
        }
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

void PropertiesPanel::showLight(Entity entity) {
  if (Application::Get()
          .getScene()
          ->getRegistry()
          .haveComponent<LightComponent>(entity)) {
    if (ImGui::TreeNode("Light")) {
      auto& lightComponent = entity.getComponent<LightComponent>();
      switch (lightComponent.type) {
        case LightType::Direction: {
          ImGui::DragFloat3("direction", &lightComponent.direction.x);
          break;
        }
        case LightType::Point: {
          ImGui::DragFloat("constant", &lightComponent.constant, 0.05, 0, 1);
          ImGui::DragFloat("linear", &lightComponent.linear, 0.05, 0, 1);
          ImGui::DragFloat("quadratic", &lightComponent.quadratic, 0.05, 0, 1);
          break;
        }
        case LightType::Spot: {
          ImGui::DragFloat3("direction", &lightComponent.direction.x);
          ImGui::DragFloat("cutOff", &lightComponent.cutOff);
          ImGui::DragFloat("outerCutOff", &lightComponent.outerCutOff);
          ImGui::DragFloat("constant", &lightComponent.constant, 0.05, 0, 1);
          ImGui::DragFloat("linear", &lightComponent.linear, 0.05, 0, 1);
          ImGui::DragFloat("quadratic", &lightComponent.quadratic, 0.05, 0, 1);
          break;
        }
      }
      ImGui::DragFloat3("ambient", &lightComponent.ambient.x, 0.05, 0, 1);
      ImGui::DragFloat3("diffuse", &lightComponent.diffuse.x, 0.05, 0, 1);
      ImGui::DragFloat3("specular", &lightComponent.specular.x, 0.05, 0, 1);

      ImGui::TreePop();
    }
  }
}

}  // namespace deft
