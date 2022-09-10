#include "app/application.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "math/math.h"
#include "util/obj_loader.h"
#include "pch.h"

namespace deft {

Application* Application::_s_instance;

Application::Application() {
  if (_s_instance) {
    std::cerr
        << "Application::Application There is already a running application!"
        << std::endl;
    return;
  }
  _s_instance = this;

  _window           = std::make_unique<Window>(1600, 900, "Deft");
  _context          = std::make_unique<GraphicContext>(_window->getHandler());
  _scene            = std::make_unique<Scene>();
  _renderer         = std::make_unique<Renderer>();
  _inputManager     = std::make_unique<InputManager>(_window->getHandler());
  _cameraController = std::make_shared<CameraController>();
}

Application::~Application() {}

void Application::run() {
  float offset = 0.0f;
  float delta  = 1.0f;
  float t      = 0.0f;

  math::Vector3 cameraPos{0.0f};
  math::Vector3 objectPos{0.0f, 0.0f, -2.0f};
  while (!_window->isClosed()) {
    // get deltaTime
    float tt = (float)glfwGetTime();
    float dt = tt - t;
    t        = tt;

    _inputManager->tick();

    // Logic update
    if (_inputManager->isMouseButtonPress(MouseButton::Right)) {
      glfwSetInputMode(_window->getHandler(), GLFW_CURSOR,
                       GLFW_CURSOR_DISABLED);
      _cameraController->tick(dt);
    } else {
      glfwSetInputMode(_window->getHandler(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    _scene->tick(dt);

    // Render
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _renderer->begin(_cameraController->getCamera());
    _scene->render(*_renderer);
    _renderer->end();

    // Window update
    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

InputManager& Application::getInputManager() { return *_inputManager; }

Scene& Application::getScene() { return *_scene; }

}  // namespace deft
