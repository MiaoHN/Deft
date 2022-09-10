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
    std::cerr << "GraphicContext::GraphicContext Failed to initialize GLAD!"
              << std::endl;
    exit(-1);
  }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);
  glfwSwapInterval(1);

  const unsigned char* str1 = glGetString(GL_VERSION);
  const unsigned char* str2 = glGetString(GL_VENDOR);
  std::cerr << "Version: " << str1 << std::endl;
  std::cerr << "Vendor:  " << str2 << std::endl;
}

GraphicContext::~GraphicContext() {}

void GraphicContext::swapBuffers() { glfwSwapBuffers(_handler); }

}  // namespace deft
