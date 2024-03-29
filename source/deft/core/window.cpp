#include "core/window.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "core/application.h"
#include "pch.h"

namespace deft {

void GLFWErrorCallback(int error_code, const char* description) {
  LOG_CORE_ERROR("GLFW Error(%d): %s", error_code, description);
  LOG_CLIENT_ERROR("GLFW Error(%d): %s", error_code, description);
}

Window::Window(int width, int height, const std::string& title)
    : _width(width), _height(height), _title(title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
  if (!_window) {
    LOG_CORE_FATAL("Window::Window Error occur when create GLFWwindow!");
    exit(-1);
  }

  int            w, h, n;
  unsigned char* data = stbi_load("assets/logo/logo.png", &w, &h, &n, 0);
  GLFWimage      img;
  img.width  = w;
  img.height = h;
  img.pixels = data;
  glfwSetWindowIcon(_window, 1, &img);

  glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);

  glfwSetErrorCallback(GLFWErrorCallback);

  glfwSetWindowUserPointer(_window, &Application::Get());

  _context = GraphicContext::Create(_window);
  _context->init();
}

Window::~Window() {
  if (_window) glfwDestroyWindow(_window);
  glfwTerminate();
}

int Window::getWidth() const { return _width; }
int Window::getHeight() const { return _height; }

bool Window::isClosed() const { return glfwWindowShouldClose(_window); }

void Window::setClose(bool flag) { glfwSetWindowShouldClose(_window, flag); }

GLFWwindow* Window::getHandler() const { return _window; }

std::string Window::getTitle() const { return _title; }

void Window::setTitle(const std::string& title) {
  _title = title;
  glfwSetWindowTitle(_window, _title.c_str());
}

void Window::tick() const {
  glfwPollEvents();
  _context->swapBuffers();
}

}  // namespace deft
