#include "render/texture.h"

#include "platform/render/opengl/opengl_texture.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<Texture> Texture::Create(int width, int height) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLTexture>(width, height);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

std::shared_ptr<Texture> Texture::Create(const std::string& path) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLTexture>(path);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft
