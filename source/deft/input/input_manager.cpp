#include "input_manager.h"

#include <GLFW/glfw3.h>

#include "app/application.h"

namespace deft {

InputManager::InputManager(GLFWwindow* handler) : _handler(handler) {
  glfwSetKeyCallback(_handler, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mod) {
    auto    app     = (Application*)glfwGetWindowUserPointer(window);
    auto&   input   = app->getInputManager();
    KeyCode keyCode = static_cast<KeyCode>(key);
    auto    iter    = input._keyCallbacks.find(keyCode);
    if (iter == input._keyCallbacks.end()) return;
    auto& callbacks = input._keyCallbacks[keyCode];
    for (auto& callback : callbacks) {
      callback.second();
    }
  });
  glfwSetScrollCallback(
      _handler, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto  app   = (Application*)glfwGetWindowUserPointer(window);
        auto& input = app->getInputManager();
        for (auto& scrollCallback : input._scrollCallbacks) {
          scrollCallback.second(xoffset, yoffset);
        }
      });
}

InputManager::~InputManager() {}

bool InputManager::isKeyPress(KeyCode key) {
  return glfwGetKey(_handler, static_cast<int>(key)) == GLFW_PRESS;
}

bool InputManager::isMouseButtonPress(MouseButton button) {
  return glfwGetMouseButton(_handler, static_cast<int>(button)) == GLFW_PRESS;
}

void InputManager::addKeyCallback(KeyCode key, const std::string& funcName,
                                  std::function<void()> callback) {
  _keyCallbacks[key][funcName] = callback;
}

void InputManager::delKeyCallback(KeyCode key, const std::string& funcName) {
  auto iter1 = _keyCallbacks.find(key);
  if (iter1 == _keyCallbacks.end()) return;
  auto iter2 = _keyCallbacks[key].find(funcName);
  if (iter2 == _keyCallbacks[key].end()) return;
  _keyCallbacks[key].erase(iter2);
}

void InputManager::addScrollCallback(
    const std::string& funcName, std::function<void(double, double)> callback) {
  _scrollCallbacks[funcName] = callback;
}

void InputManager::delScrollCallback(const std::string& funcName) {
  auto iter = _scrollCallbacks.find(funcName);
  if (iter == _scrollCallbacks.end()) return;
  _scrollCallbacks.erase(iter);
}

void InputManager::tick() {
  double x, y;
  glfwGetCursorPos(_handler, &x, &y);
  _offsetPos = {(float)x - _cursorPos.x, (float)y - _cursorPos.y};
  _cursorPos = {(float)x, (float)y};
}

math::Vector2 InputManager::getMousePosition() { return _cursorPos; }

math::Vector2 InputManager::getMouseOffset() { return _offsetPos; }

math::Vector2 InputManager::getScrollOffset() { return _scrollOffset; }

}  // namespace deft
