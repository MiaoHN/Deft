#ifndef __DEFT_APPLICATION_H__
#define __DEFT_APPLICATION_H__

#include <memory>

#include "controller/camera_controller.h"
#include "render/graphic_context.h"
#include "render/index_buffer.h"
#include "render/shader.h"
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

  Window& getWindow();

 private:
  std::unique_ptr<Window>         _window;
  std::unique_ptr<GraphicContext> _context;

  std::shared_ptr<VertexArray>  _vao;
  std::shared_ptr<VertexBuffer> _vbo;
  std::shared_ptr<IndexBuffer>  _ebo;
  std::shared_ptr<Shader>       _shader;

  std::shared_ptr<CameraController> _cameraController;

  static Application* _s_instance;
};

}  // namespace deft

#endif  // __DEFT_APPLICATION_H__