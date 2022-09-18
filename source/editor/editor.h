#ifndef __DEFT_EDITOR_H__
#define __DEFT_EDITOR_H__

#include "deft.h"
#include "editor_camera.h"
#include "gui/log_panel.h"

namespace deft {

class Editor : public Application {
 public:
  void initialize() override;

  void tick(float dt) override;

 private:
  std::shared_ptr<Scene> _scene;

  std::shared_ptr<EditorCamera> _editorCamera;

  std::shared_ptr<FrameBuffer> _frameBuffer;

  std::shared_ptr<LogPanel> _logPanel;

  bool   _isHovered = false;
  bool   _selected  = false;
  Entity _selectedEntity;

  math::Vector2 _viewportBounds[2];

  int _gizmoType = -1;
};

Application* CreateApplication();

}  // namespace deft

#endif  // __DEFT_EDITOR_H__