#include "app/application.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "render/uniform_buffer.h"
#include "math/math.h"
#include "ecs/components/transform.h"
#include "ecs/components/mesh.h"
#include "util/obj_loader.h"
#include "pch.h"
#include "log/log.h"

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

  _window           = std::make_unique<Window>(1600, 900, "Deft");
  _context          = std::make_unique<GraphicContext>(_window->getHandler());
  _scene            = std::make_shared<Scene>();
  _inputManager     = std::make_unique<InputManager>(_window->getHandler());
  _gui              = std::make_unique<Gui>();
  _cameraController = std::make_shared<CameraController>();

  _frameBuffer =
      FrameBuffer::Create({getWindow().getWidth(), getWindow().getHeight()});

  ShaderLib::Add("default",
                 std::make_shared<Shader>("assets/shader/default.vert",
                                          "assets/shader/default.frag"));
  UniformBufferLib::Add("cameraUniform",
                        std::make_shared<UniformBuffer>(sizeof(CameraData), 0));
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

    // fps calculate
    if (tt - _lastSecond >= 1.0f) {
      _lastSecond = tt;
      _fps        = _frameCount;
      _frameCount = 0;
    }
    ++_frameCount;

    _inputManager->tick();

    // Logic update
    if (_gui->isScenePanelHovered()) {
      if (_inputManager->isMouseButtonPress(MouseButton::Right)) {
        // glfwSetInputMode(_window->getHandler(), GLFW_CURSOR,
        //                  GLFW_CURSOR_DISABLED);
        _cameraController->setEnable(true);
      } else {
        // glfwSetInputMode(_window->getHandler(), GLFW_CURSOR,
        //                  GLFW_CURSOR_NORMAL);
        _cameraController->setEnable(false);
      }
    } else {
      // glfwSetInputMode(_window->getHandler(), GLFW_CURSOR,
      //                  GLFW_CURSOR_NORMAL);
      _cameraController->setEnable(false);
    }

    _cameraController->tick(dt);
    _gui->update();

    _frameBuffer->bind();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _scene->updateEditMode(dt, _cameraController->getCamera());
    _frameBuffer->unBind();

    _gui->draw();

    // Window update
    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

InputManager& Application::getInputManager() { return *_inputManager; }

std::shared_ptr<Scene>& Application::getScene() { return _scene; }

std::shared_ptr<FrameBuffer>& Application::getFrameBuffer() {
  return _frameBuffer;
}

int Application::getFps() { return _fps; }

}  // namespace deft
