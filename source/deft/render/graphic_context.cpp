#include "render/graphic_context.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "pch.h"

namespace deft {

GraphicContext::GraphicContext(GLFWwindow* handler) : _handler(handler) {
  glfwMakeContextCurrent(_handler);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_CORE_FATAL("GraphicContext::GraphicContext Failed to initialize GLAD!");
    exit(-1);
  }

  glfwSwapInterval(1);

  const unsigned char* str1 = glGetString(GL_VERSION);
  const unsigned char* str2 = glGetString(GL_VENDOR);
  LOG_CLIENT_INFO("Version: %s", str1);
  LOG_CLIENT_INFO("Vendor:  %s", str2);
}

GraphicContext::~GraphicContext() {}

void GraphicContext::swapBuffers() { glfwSwapBuffers(_handler); }

}  // namespace deft
