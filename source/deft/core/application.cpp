#include "core/application.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "pch.h"

namespace deft {

Application* Application::_s_instance;

Application::Application() {
  if (_s_instance) {
    LOG_CORE_FATAL(
        "Application::Application There is already a running application!");
    return;
  }
  _s_instance = this;

  _lastSecond = 0.0f;
  _frameCount = 0;
  _fps        = 0;

  _window  = std::make_unique<Window>(1600, 900, "Deft");
  _context = std::make_unique<GraphicContext>(_window->getHandler());
}

Application::~Application() {}

void Application::run() {
  float t = 0.0f;
  while (!_window->isClosed()) {
    // get deltaTime
    float tt = (float)glfwGetTime();
    float dt = tt - t;
    t        = tt;

    for (auto& layer : _layers) {
      layer->update(dt);
    }

    // fps calculate
    if (tt - _lastSecond >= 1.0f) {
      _lastSecond = tt;
      _fps        = _frameCount;
      _frameCount = 0;
    }
    ++_frameCount;

    // Window update
    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

void Application::pushLayer(Layer* layer) { _layers.push_back(layer); }

int Application::getFps() { return _fps; }

}  // namespace deft
