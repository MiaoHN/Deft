#include "gui/scene_panel.h"

#include "app/application.h"

namespace deft {

ScenePanel::ScenePanel() { _scene = Application::Get().getScene(); }

ScenePanel::~ScenePanel() {}

void ScenePanel::update() {
  unsigned int sceneTexture = _scene->getFrameBuffer()->getColorAttachment();
  ImGui::Begin("Scene");
  if (ImGui::IsWindowHovered()) {
    _isHovered = true;
  } else {
    _isHovered = false;
  }
  ImGui::Image(reinterpret_cast<void*>(sceneTexture), ImVec2{800, 450},
               ImVec2{0, 1}, ImVec2{1, 0});
  ImGui::End();
}

bool ScenePanel::isHovered() { return _isHovered; }

}  // namespace deft
