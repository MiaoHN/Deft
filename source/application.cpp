#include "application.h"

#include <glad/glad.h>

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
      -0.5f, -0.5f, 0.0f,  //
      -0.5f, 0.5f,  0.0f,  //
      0.0f,  0.5f,  0.0f,  //
  };

  _vao = std::make_shared<VertexArray>();
  _vbo = std::make_shared<VertexBuffer>(vertices);
  _vbo->setElements({
      {"aPos", ElementType::Float3},
  });

  _vao->bind();
  _vbo->bind();
  _vao->unBind();
  _vbo->unBind();

  _shader = std::make_shared<Shader>("assets/shader/default.vert",
                                     "assets/shader/default.frag");
}

Application::~Application() {}

void Application::run() {
  while (!_window->isClosed()) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _vao->bind();
    _shader->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    _window->pollEvents();
    _context->swapBuffers();
  }
}

Application& Application::Get() { return *_s_instance; }

}  // namespace deft
