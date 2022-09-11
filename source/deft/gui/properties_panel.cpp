#include "gui/properties_panel.h"

#include <imgui.h>

#include "components/component.h"

namespace deft {

PropertiesPanel::PropertiesPanel() {}

PropertiesPanel::~PropertiesPanel() {}

void PropertiesPanel::update(
    const std::shared_ptr<HierarchyPanel>& hierarchyPanel) {
  ImGui::Begin("Properties");

  if (hierarchyPanel->haveSelectedEntity()) {
    Entity entity = hierarchyPanel->getSelectedEntity();

    // 显示位置信息
    showTransform(entity);

    // 显示材质信息
    showTexture(entity);
  }
  ImGui::End();
}

void PropertiesPanel::showTransform(Entity entity) {
  auto& transform = g_registry.getComponent<Transform>(entity);
  ImGui::SliderFloat3("Position", &transform.position.x, -5.0f, 5.0f);
}

void PropertiesPanel::showTexture(Entity entity) {
  if (g_registry.haveComponent<Renderable>(entity)) {
    auto& renderable = g_registry.getComponent<Renderable>(entity);

    for (auto& texture : renderable.model->getTextures()) {
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
  }
}

}  // namespace deft