#include "render/render_command.h"

namespace deft {

std::unique_ptr<RenderAPI> RenderCommand::_api = RenderAPI::Create();

void RenderCommand::Init() { _api->init(); }

void RenderCommand::ClearColor(const math::Vector4& color) {
  _api->clearColor(color);
}

void RenderCommand::Clear() { _api->clear(); }

void RenderCommand::DrawIndex(const std::shared_ptr<VertexArray>& vertexArray,
                              unsigned int                        count) {
  _api->drawIndex(vertexArray, count);
}

}  // namespace deft
