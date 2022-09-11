#include "gui/properties_panel.h"

#include <imgui.h>

#include "components/transform.h"

namespace deft {

PropertiesPanel::PropertiesPanel() {}

PropertiesPanel::~PropertiesPanel() {}

void PropertiesPanel::update(
    const std::shared_ptr<HierarchyPanel>& hierarchyPanel) {
  ImGui::Begin("Properties");
  if (hierarchyPanel->haveSelectedEntity()) {
    auto& transform =
        g_registry.getComponent<Transform>(hierarchyPanel->getSelectedEntity());
    ImGui::SliderFloat3("Position", &transform.position.x, -5.0f, 5.0f);
  }
  ImGui::End();
}

}  // namespace deft
