#include "gui/hierarchy_panel.h"

#include <imgui.h>

namespace deft {

HierarchyPanel::HierarchyPanel() {}

HierarchyPanel::~HierarchyPanel() {}

void HierarchyPanel::update() {
  ImGui::Begin("Scene Hierarchy");
  for (auto& entity : g_registry.getEntiesUsed()) {
    std::string str = "entity" + std::to_string(static_cast<int>(entity));
    if (ImGui::Button(str.c_str())) {
      _selected       = true;
      _selectedEntity = entity;
    }
  }

  ImGui::End();
}

Entity HierarchyPanel::getSelectedEntity() { return _selectedEntity; }

bool HierarchyPanel::haveSelectedEntity() { return _selected; }

}  // namespace deft
