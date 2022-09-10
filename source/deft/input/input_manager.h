#ifndef __DEFT_INPUT_MANAGER_H__
#define __DEFT_INPUT_MANAGER_H__

#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>

#include "input/key_code.h"
#include "input/mouse_button_code.h"
#include "math/math.h"

struct GLFWwindow;

namespace deft {

// callback 最好前跟类名，例如 'Object::func'
#define INPUT_FUNC_BIND(callback) #callback, std::bind(callback, this)

#define IS_KEY_PRESS(key) Application::Get().getInputManager().isKeyPress(key)
#define GET_CURSOR_OFFSET() \
  Application::Get().getInputManager().getMouseOffset()
#define GET_SCROLL_OFFSET() \
  Application::Get().getInputManager().getScrollOffset()

class InputManager {
 public:
  InputManager(GLFWwindow* handler);
  ~InputManager();

  bool isKeyPress(KeyCode key);

  bool isMouseButtonPress(MouseButton button);

  void addKeyCallback(KeyCode key, const std::string& funcName,
                      std::function<void()> callback);

  void delKeyCallback(KeyCode key, const std::string& funcName);

  void addScrollCallback(const std::string&                  funcName,
                         std::function<void(double, double)> callback);
  void delScrollCallback(const std::string& funcName);

  void tick();

  math::Vector2 getMousePosition();
  math::Vector2 getMouseOffset();
  math::Vector2 getScrollOffset();

 private:
  GLFWwindow* _handler;

  math::Vector2 _scroll;
  math::Vector2 _scrollOffset;

  math::Vector2 _cursorPos;
  math::Vector2 _offsetPos;

  std::unordered_map<KeyCode,
                     std::unordered_map<std::string, std::function<void()>>>
      _keyCallbacks;
  std::unordered_map<std::string, std::function<void(double, double)>>
      _scrollCallbacks;
};

}  // namespace deft

#endif  // __DEFT_INPUT_MANAGER_H__