#include "input/input.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/application.h"

namespace deft {

bool Input::IsMouseButtonPress(MouseButton button) {
  auto window = Application::Get().getWindow().getHandler();
  return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
}

bool Input::IsKeyPress(KeyCode key) {
  auto window = Application::Get().getWindow().getHandler();
  return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
}

math::Vector2 Input::GetMousePosition() {
  double x, y;
  auto   window = Application::Get().getWindow().getHandler();
  glfwGetCursorPos(window, &x, &y);
  return {(float)x, (float)y};
}

}  // namespace deft
