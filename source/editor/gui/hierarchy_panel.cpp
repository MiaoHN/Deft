#include "gui/hierarchy_panel.h"

#include <imgui_internal.h>

namespace deft {

HierarchyPanel::HierarchyPanel(Registry* registry) : _registry(registry) {}

HierarchyPanel::~HierarchyPanel() {}

void HierarchyPanel::update() {
  ImGui::Begin("Scene Hierarchy");
  if (ImGui::Button("Add")) {
    _registry->createEntity();
  }

  for (auto& entity : _registry->getEntiesUsed()) {
    if (ImGui::Button(entity.getName().c_str())) {
      _selected       = true;
      _selectedEntity = entity;
    }
  }

  ImGui::End();
}

Entity HierarchyPanel::getSelectedEntity() { return _selectedEntity; }

bool HierarchyPanel::haveSelectedEntity() { return _selected; }

}  // namespace deft
