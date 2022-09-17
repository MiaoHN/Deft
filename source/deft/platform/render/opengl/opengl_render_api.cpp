#include "platform/render/opengl/opengl_render_api.h"

#include <glad/glad.h>

namespace deft {

void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id,
                           unsigned severity, int length, const char* message,
                           const void* userParam) {
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      LOG_CORE_FATAL(message);
      return;
    case GL_DEBUG_SEVERITY_MEDIUM:
      LOG_CORE_ERROR(message);
      return;
    case GL_DEBUG_SEVERITY_LOW:
      LOG_CORE_WARN(message);
      return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      LOG_CORE_INFO(message);
      return;
  }

  LOG_CORE_FATAL("Unknown severity level!");
  exit(-1);
}

void OpenGLRenderAPI::init() {
#ifdef DEFT_DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(OpenGLMessageCallback, nullptr);

  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LINE_SMOOTH);
}

void OpenGLRenderAPI::setViewPort(int x, int y, int width, int height) {
  glViewport(x, y, width, height);
}

void OpenGLRenderAPI::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderAPI::clearColor(const math::Vector4& color) {
  glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRenderAPI::drawIndex(const std::shared_ptr<VertexArray>& vao,
                                unsigned int                        count) {
  vao->bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

}  // namespace deft
