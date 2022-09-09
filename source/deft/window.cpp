#include "window.h"

#include <GLFW/glfw3.h>

#include "pch.h"

namespace deft {

void GLFWErrorCallback(int error_code, const char* description) {
  std::cerr << "GLFW Error(" << error_code << "): " << description << std::endl;
}

Window::Window(int width, int height, const std::string& title)
    : _width(width), _height(height), _title(title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
  if (!_window) {
    std::cerr << "Window::Window Error occur when create GLFWwindow!"
              << std::endl;
    exit(-1);
  }

  glfwSetErrorCallback(GLFWErrorCallback);
}

Window::~Window() {
  if (_window) glfwDestroyWindow(_window);
  glfwTerminate();
}

int Window::getWidth() const { return _width; }
int Window::getHeight() const { return _height; }

bool Window::isClosed() const { return glfwWindowShouldClose(_window); }

GLFWwindow* Window::getHandler() const { return _window; }

std::string Window::getTitle() const { return _title; }

void Window::setTitle(const std::string& title) {
  _title = title;
  glfwSetWindowTitle(_window, _title.c_str());
}

void Window::pollEvents() const { glfwPollEvents(); }

}  // namespace deft