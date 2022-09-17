#include "gui/properties_panel.h"

namespace deft {

PropertiesPanel::PropertiesPanel(Registry* registry) : _registry(registry) {}

PropertiesPanel::~PropertiesPanel() {}

void PropertiesPanel::update(
    const std::shared_ptr<HierarchyPanel>& hierarchyPanel) {
  ImGui::Begin("Properties");

  if (hierarchyPanel->haveSelectedEntity()) {
    Entity entity = hierarchyPanel->getSelectedEntity();

    ImGui::LabelText("Entity Name", entity.getName().c_str());

    char buf[128] = "";
    if (ImGui::InputText("Rename", buf, 128)) {
      std::string newName = std::string(buf, strlen(buf));
      entity.setName(newName);
    }

    if (ImGui::Button("Add Transform")) {
      if (!entity.haveComponent<TransformComponent>()) {
        entity.addComponent(TransformComponent());
      }
    }
    if (ImGui::Button("Add Mesh(cube)")) {
      if (!entity.haveComponent<MeshComponent>()) {
        if (!entity.haveComponent<TransformComponent>()) {
          entity.addComponent(TransformComponent());
        }
        MeshComponent meshComponent;
        meshComponent.mesh = Mesh::Cube();
        meshComponent.mesh->addTexture(
            TextureType::Diffuse,
            Texture::Create("assets/texture/container.jpg"));
        unsigned int color   = 0xffffffff;
        auto         texture = Texture::Create(1, 1);
        texture->setData(&color, sizeof(color));
        meshComponent.mesh->addTexture(TextureType::Specular, texture);
        entity.addComponent(meshComponent);
      }
    }

    // 显示位置信息
    showTransform(entity);

    // 显示材质信息
    showMesh(entity);

    // 显示光照信息
    showLight(entity);
  }
  ImGui::End();
}

void PropertiesPanel::showTransform(Entity entity) {
  if (_registry->haveComponent<TransformComponent>(entity)) {
    auto& transform = _registry->getComponent<TransformComponent>(entity);
    if (ImGui::TreeNode("Transform")) {
      ImGui::DragFloat3("Position", &transform.position.x);
      ImGui::DragFloat3("Rotation", &transform.rotation.x);
      ImGui::DragFloat3("Scale", &transform.scale.x);
      ImGui::TreePop();
    }
  }
}

void PropertiesPanel::showMesh(Entity entity) {
  if (_registry->haveComponent<MeshComponent>(entity)) {
    auto& meshComponent = _registry->getComponent<MeshComponent>(entity);
    if (ImGui::TreeNode("Mesh")) {
      auto& textures = meshComponent.mesh->getTextures();
      if (textures.find(TextureType::Diffuse) != textures.end()) {
        unsigned int textureId = textures[TextureType::Diffuse]->getId();
        ImGui::Text("Diffuse");
        ImGui::Image(reinterpret_cast<void*>(textureId), ImVec2{80.0f, 80.0f},
                     ImVec2{0, 1}, ImVec2{1, 0});
        ImGui::Separator();
      }
      if (textures.find(TextureType::Specular) != textures.end()) {
        unsigned int textureId = textures[TextureType::Specular]->getId();
        ImGui::Text("Specular");
        ImGui::Image(reinterpret_cast<void*>(textureId), ImVec2{80.0f, 80.0f},
                     ImVec2{0, 1}, ImVec2{1, 0});
        ImGui::Separator();
      }
      ImGui::TreePop();
    }
  }
}

void PropertiesPanel::showLight(Entity entity) {
  if (_registry->haveComponent<LightComponent>(entity)) {
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
