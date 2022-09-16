#include "render/render_command.h"

#include <glad/glad.h>

namespace deft {

void RenderCommand::ClearColor(const math::Vector4& color) {
  glClearColor(color.x, color.y, color.z, color.w);
}

void RenderCommand::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray,
                              unsigned int                        count) {
  vertexArray->bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void RenderCommand::DepthTest(bool flag) {
  if (flag) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

void RenderCommand::CullFace(bool flag) {
  if (flag) {
    glEnable(GL_CULL_FACE);
  } else {
    glDisable(GL_CULL_FACE);
  }
}

void RenderCommand::Multisample(bool flag) {
  if (flag) {
    glEnable(GL_MULTISAMPLE);
  } else {
    glDisable(GL_MULTISAMPLE);
  }
}

}  // namespace deft
