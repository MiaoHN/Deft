#ifndef __DEFT_EDITOR_H__
#define __DEFT_EDITOR_H__

#include "deft.h"
#include "gui/gui.h"

namespace deft {

class Editor : public Application {
 public:
  void initialize() override;

  void tick(float dt) override;

 private:
  std::shared_ptr<Scene> _scene;

  std::unique_ptr<Gui>              _gui;
  std::shared_ptr<CameraController> _editorCameraController;

  std::shared_ptr<FrameBuffer> _frameBuffer;
};

Application* CreateApplication();

}  // namespace deft

#endif  // __DEFT_EDITOR_H__