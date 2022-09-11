#include "gui/scene_panel.h"

#include "app/application.h"

namespace deft {

ScenePanel::ScenePanel() { _scene = Application::Get().getScene(); }

ScenePanel::~ScenePanel() {}

void ScenePanel::update() {
  unsigned int sceneTexture = _scene->getFrameBuffer()->getColorAttachment();
  ImGui::Begin("Scene");
  ImGui::Image(reinterpret_cast<void*>(sceneTexture), ImVec2{800, 450},
               ImVec2{0, 1}, ImVec2{1, 0});
  ImGui::End();
}

}  // namespace deft
