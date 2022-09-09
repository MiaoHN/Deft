#include "application.h"

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

  _window  = std::make_unique<Window>(1600, 900, "Deft");
  _context = std::make_unique<GraphicContext>(_window->getHandler());

  glfwSetInputMode(_window->getHandler(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  _inputManager = std::make_shared<InputManager>(_window->getHandler());

  _inputManager->addCallback(KeyCode::Escape,
                             INPUT_FUNC_BIND(Application::escapePressed));

  _model = ObjLoader::Load("assets/model/standford-bunny.obj");

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
                                     "assets/shader/default.frag");

  _shader->setInt("diffuseTexture", 0);

  _texture = std::make_shared<Texture>("assets/texture/wall.jpg");

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
    _cameraController->tick(dt);

    // Render
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _model->bind();
    _shader->bind();
    _texture->bind();

    auto proj  = _cameraController->getCamera()->getProjection();
    auto view  = _cameraController->getCamera()->getView();
    auto model = math::translate(math::Matrix4(1.0f), objectPos);
    _shader->setMatrix4("transform", proj * view * model);

    glDrawElements(GL_TRIANGLES, _model->getCount(), GL_UNSIGNED_INT, nullptr);

    // Window update
    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

InputManager& Application::getInputManager() { return *_inputManager; }

void Application::escapePressed() { _window->setClose(true); }

}  // namespace deft
