#ifndef __DEFT_APPLICATION_H__
#define __DEFT_APPLICATION_H__

#include <memory>

#include "app/window.h"
#include "controller/camera_controller.h"
#include "gui/gui.h"
#include "input/input_manager.h"
#include "render/frame_buffer.h"
#include "render/graphic_context.h"
#include "render/renderer.h"
#include "scene/scene.h"

namespace deft {

class Application {
 public:
  Application();
  ~Application();

  void run();

  static Application& Get();

  Window&       getWindow();
  InputManager& getInputManager();
  Scene&        getScene();

 private:
  std::unique_ptr<Window>           _window;
  std::unique_ptr<GraphicContext>   _context;
  std::unique_ptr<Scene>            _scene;
  std::unique_ptr<InputManager>     _inputManager;
  std::unique_ptr<Renderer>         _renderer;
  std::unique_ptr<Gui>              _gui;
  std::shared_ptr<CameraController> _cameraController;

  std::shared_ptr<FrameBuffer> _sceneFrameBuffer;

  static Application* _s_instance;
};

}  // namespace deft

#endif  // __DEFT_APPLICATION_H__