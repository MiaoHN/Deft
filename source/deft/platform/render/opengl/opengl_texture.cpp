#include "platform/render/opengl/opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace deft {

OpenGLTexture::OpenGLTexture(int width, int height)
    : _width(width), _height(height) {
  _internalFormat = GL_RGBA8;
  _dataFormat     = GL_RGBA;

  glCreateTextures(GL_TEXTURE_2D, 1, &_id);
  glTextureStorage2D(_id, 1, _internalFormat, _width, _height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture::OpenGLTexture(const std::string& path) {
  stbi_set_flip_vertically_on_load(true);

  unsigned char* data =
      stbi_load(path.c_str(), &_width, &_height, &_nrChannels, 0);

  if (_nrChannels == 4) {
    _internalFormat = GL_RGBA8;
    _dataFormat     = GL_RGBA;
  } else if (_nrChannels == 3) {
    _internalFormat = GL_RGB8;
    _dataFormat     = GL_RGB;
  }

  if (!data) {
    LOG_CLIENT_ERROR("Texture::Texture Failed to load texture");
    return;
  }

  glCreateTextures(GL_TEXTURE_2D, 1, &_id);
  glTextureStorage2D(_id, 1, _internalFormat, _width, _height);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTextureSubImage2D(_id, 0, 0, 0, _width, _height, _dataFormat,
                      GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

OpenGLTexture::~OpenGLTexture() { glDeleteTextures(1, &_id); }

unsigned int OpenGLTexture::getId() { return _id; }

void OpenGLTexture::bind(int slot) const { glBindTextureUnit(slot, _id); }

void OpenGLTexture::unBind(int slot) const { glBindTextureUnit(slot, 0); }

void OpenGLTexture::setData(void* data, int size) {
  glTextureSubImage2D(_id, 0, 0, 0, _width, _height, _dataFormat,
                      GL_UNSIGNED_BYTE, data);
}

}  // namespace deft
