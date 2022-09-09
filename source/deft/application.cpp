#include "application.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "math/math.h"
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

  std::vector<float> vertices = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  //
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  //
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  //
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  //
  };

  std::vector<unsigned int> indices = {
      0, 1, 2,  //
      0, 2, 3,  //
  };

  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(vertices);
  _vbo->setElements({
      {"aPos", ElementType::Float3},
      {"aTexCoord", ElementType::Float2},
  });
  _ebo = std::make_shared<IndexBuffer>(indices);

  _vao->bind();
  _vbo->bind();
  _ebo->bind();
  _vao->unBind();
  _vbo->unBind();
  _ebo->unBind();

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
                                     "assets/shader/default.frag");

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

    // Logic update
    math::Vector3 move(0.0f);
    if (glfwGetKey(_window->getHandler(), GLFW_KEY_A) == GLFW_PRESS) {
      move.x -= 1.0f;
    } else if (glfwGetKey(_window->getHandler(), GLFW_KEY_D) == GLFW_PRESS) {
      move.x += 1.0f;
    }
    if (glfwGetKey(_window->getHandler(), GLFW_KEY_SPACE) == GLFW_PRESS) {
      move.y += 1.0f;
    } else if (glfwGetKey(_window->getHandler(), GLFW_KEY_LEFT_SHIFT) ==
               GLFW_PRESS) {
      move.y -= 1.0f;
    }
    if (glfwGetKey(_window->getHandler(), GLFW_KEY_W) == GLFW_PRESS) {
      move.z -= 1.0f;
    } else if (glfwGetKey(_window->getHandler(), GLFW_KEY_S) == GLFW_PRESS) {
      move.z += 1.0f;
    }

    _cameraController->move(move, dt);

    // Render
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _vao->bind();
    _shader->bind();

    auto proj  = _cameraController->getCamera()->getProjection();
    auto view  = _cameraController->getCamera()->getView();
    auto model = math::translate(math::Matrix4(1.0f), objectPos);
    _shader->setMatrix4("transform", proj * view * model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // Window update
    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

Window& Application::getWindow() { return *_window; }

}  // namespace deft
