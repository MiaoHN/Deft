#include "render/texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace deft {

Texture::Texture(int width, int height) : _dataType(Blank) {
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const math::Vector3& color) : _dataType(Color), _color(color) {
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);

  unsigned int colorByte1 = _color.x * 255;
  unsigned int colorByte2 = _color.y * 255;
  unsigned int colorByte3 = _color.z * 255;
  unsigned int colorByte4 = 255;

  unsigned int colorBytes = (colorByte4 << 24) | (colorByte3 << 16) |
                            (colorByte2 << 8) | (colorByte1 << 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE,
               &colorBytes);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const std::string& path) : _dataType(Image) {
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);

  int            width, height, nrChannels;
  unsigned char* data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
  if (data) {
    if (nrChannels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    } else if (nrChannels == 4) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    LOG_CLIENT_ERROR("Texture::Texture Failed to load texture");
  }
  stbi_image_free(data);
  _id = texture;
}

Texture::~Texture() { glDeleteTextures(1, &_id); }

unsigned int Texture::getId() { return _id; }

void Texture::bind(int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unBind(int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::DataType Texture::getDataType() { return _dataType; }

void Texture::setColor(const math::Vector3& color) {
  bind();

  _color = color;

  unsigned int colorByte1 = _color.x * 255;
  unsigned int colorByte2 = _color.y * 255;
  unsigned int colorByte3 = _color.z * 255;
  unsigned int colorByte4 = 255;

  unsigned int colorBytes = (colorByte4 << 24) | (colorByte3 << 16) |
                            (colorByte2 << 8) | (colorByte1 << 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE,
               &colorBytes);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unBind();
}

math::Vector3& Texture::getColor() { return _color; }

std::shared_ptr<Texture> Texture::Create(int width, int height) {
  return std::make_shared<Texture>(width, height);
}

std::shared_ptr<Texture> Texture::Create(const math::Vector3& color) {
  return std::make_shared<Texture>(color);
}

std::shared_ptr<Texture> Texture::Create(const std::string& path) {
  return std::make_shared<Texture>(path);
}

}  // namespace deft
