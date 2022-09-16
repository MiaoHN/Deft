#ifndef __DEFT_APPLICATION_H__
#define __DEFT_APPLICATION_H__

#include <memory>
#include <vector>

#include "core/layer.h"
#include "core/window.h"
#include "render/graphic_context.h"

namespace deft {

class Application {
 public:
  Application();
  ~Application();

  void run();

  static Application& Get();

  Window& getWindow();

  void pushLayer(Layer* layer);

  int getFps();

 private:
  std::vector<Layer*> _layers;

  std::unique_ptr<Window>         _window;
  std::unique_ptr<GraphicContext> _context;

  float _lastSecond;
  int   _frameCount;
  int   _fps;

  static Application* _s_instance;
};

Application* CreateApplication();

}  // namespace deft

#endif  // __DEFT_APPLICATION_H__