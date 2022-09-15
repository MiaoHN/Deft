#include "gui/hierarchy_panel.h"

#include <imgui.h>

#include "app/application.h"

namespace deft {

HierarchyPanel::HierarchyPanel() {}

HierarchyPanel::~HierarchyPanel() {}

void HierarchyPanel::update() {
  ImGui::Begin("Scene Hierarchy");
  for (auto& entity :
       Application::Get().getScene()->getRegistry().getEntiesUsed()) {
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
