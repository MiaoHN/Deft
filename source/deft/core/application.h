#ifndef __DEFT_APPLICATION_H__
#define __DEFT_APPLICATION_H__

#include <memory>
#include <vector>

#include "core/timer.h"
#include "core/window.h"

namespace deft {

class Application {
 public:
  Application();
  ~Application();

  void run();

  virtual void initialize() = 0;
  virtual void tick(float dt) {}

  static Application& Get();

  Window& getWindow();

  int getFps();

 private:
  void makeInstance();

 private:
  std::unique_ptr<Window> _window;
  std::unique_ptr<Timer>  _timer;

  static Application* _s_instance;
};

Application* CreateApplication();

}  // namespace deft

#endif  // __DEFT_APPLICATION_H__