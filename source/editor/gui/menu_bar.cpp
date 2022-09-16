#include "gui/menu_bar.h"

#include "deft.h"

namespace deft {

MenuBar::MenuBar() {}

MenuBar::~MenuBar() {}

void MenuBar::update() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("Open", nullptr);
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

}  // namespace deft
