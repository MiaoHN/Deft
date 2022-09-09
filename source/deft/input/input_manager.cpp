#include "input_manager.h"

#include <GLFW/glfw3.h>

#include "application.h"

namespace deft {

InputManager::InputManager(GLFWwindow* handler) : _handler(handler) {
  glfwSetKeyCallback(_handler, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mod) {
    auto    app     = (Application*)glfwGetWindowUserPointer(window);
    auto&   input   = app->getInputManager();
    KeyCode keyCode = static_cast<KeyCode>(key);
    auto    iter    = input._callbacks.find(keyCode);
    if (iter == input._callbacks.end()) return;
    auto& callbacks = input._callbacks[keyCode];
    for (auto& callback : callbacks) {
      callback.second();
    }
  });
}

InputManager::~InputManager() {}

bool InputManager::isKeyPress(KeyCode key) {
  return glfwGetKey(_handler, static_cast<int>(key)) == GLFW_PRESS;
}

void InputManager::addCallback(KeyCode key, const std::string& funcName,
                               std::function<void()> callback) {
  _callbacks[key][funcName] = callback;
}

void InputManager::delCallback(KeyCode key, const std::string& funcName) {
  auto iter1 = _callbacks.find(key);
  if (iter1 == _callbacks.end()) return;
  auto iter2 = _callbacks[key].find(funcName);
  if (iter2 == _callbacks[key].end()) return;
  _callbacks[key].erase(iter2);
}

void InputManager::tick() {
  double x, y;
  glfwGetCursorPos(_handler, &x, &y);
  _offsetPos = {(float)x - _cursorPos.x, (float)y - _cursorPos.y};
  _cursorPos = {(float)x, (float)y};
}

math::Vector2 InputManager::getMousePosition() { return _cursorPos; }

math::Vector2 InputManager::getMouseOffset() { return _offsetPos; }

void InputManager::processKey(GLFWwindow* window, int key, int scancode,
                              int action, int mod) {}

}  // namespace deft
