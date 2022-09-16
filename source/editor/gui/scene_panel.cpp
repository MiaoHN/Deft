#include "gui/scene_panel.h"

namespace deft {

ScenePanel::ScenePanel(Registry* registry) : _registry(registry) {
  _sceneSize = {992.0f, 558.0f};
}

ScenePanel::~ScenePanel() {}

void ScenePanel::update(std::shared_ptr<FrameBuffer> buffer) {
  unsigned int sceneTexture = buffer->getColorAttachment();
  ImGui::Begin("Scene");
  if (ImGui::IsWindowHovered()) {
    _isHovered = true;
  } else {
    _isHovered = false;
  }
  ImGui::Image(reinterpret_cast<void*>(sceneTexture),
               ImVec2{_sceneSize.x, _sceneSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
  ImGui::End();
}

bool ScenePanel::isHovered() { return _isHovered; }

}  // namespace deft
