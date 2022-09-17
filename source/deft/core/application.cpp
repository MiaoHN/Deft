#include "core/application.h"

#include "pch.h"
#include "render/render_api.h"
#include "render/renderer.h"

namespace deft {

Application* Application::_s_instance;

Application::Application() {
  makeInstance();

  RenderAPI::Set(RenderAPI::OpenGL);

  _window = std::make_unique<Window>(1600, 900, "Deft");
  _timer  = std::make_unique<Timer>();

  _timer->initialize();

  Renderer::Init();
}

Application::~Application() {}

void Application::run() {
  while (!_window->isClosed()) {
    _timer->tick();

    tick(_timer->getDeltaTime());

    _window->tick();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

int Application::getFps() { return _timer->getFps(); }

void Application::makeInstance() {
  if (_s_instance) {
    LOG_CORE_FATAL(
        "Application::Application There is already a running application!");
    return;
  }
  _s_instance = this;
}

}  // namespace deft
