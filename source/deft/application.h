#ifndef __DEFT_APPLICATION_H__
#define __DEFT_APPLICATION_H__

#include <memory>

#include "controller/camera_controller.h"
#include "input/input_manager.h"
#include "render/graphic_context.h"
#include "render/index_buffer.h"
#include "render/model.h"
#include "render/shader.h"
#include "render/texture.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"
#include "window.h"

namespace deft {

class Application {
 public:
  Application();
  ~Application();

  void run();

  static Application& Get();

  Window&       getWindow();
  InputManager& getInputManager();

 private:
  void escapePressed();

 private:
  std::unique_ptr<Window>         _window;
  std::unique_ptr<GraphicContext> _context;

  std::shared_ptr<Model>   _model;
  std::shared_ptr<Texture> _texture;
  std::shared_ptr<Shader>  _shader;

  std::shared_ptr<InputManager>     _inputManager;
  std::shared_ptr<CameraController> _cameraController;

  static Application* _s_instance;
};

}  // namespace deft

#endif  // __DEFT_APPLICATION_H__