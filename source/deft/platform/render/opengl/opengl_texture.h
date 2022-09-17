#ifndef __DEFT_OPENGL_TEXTURE_H__
#define __DEFT_OPENGL_TEXTURE_H__

#include "render/texture.h"

namespace deft {

class OpenGLTexture : public Texture {
 public:
  OpenGLTexture(int width, int height);
  OpenGLTexture(const std::string& path);
  ~OpenGLTexture();

  unsigned int getId() override;

  void bind(int slot = 0) const override;
  void unBind(int slot = 0) const override;

  void setData(void* data, int size) override;

 private:
  unsigned int _id;

  int _width;
  int _height;
  int _nrChannels;

  unsigned int _dataFormat;
  unsigned int _internalFormat;

  void* _data;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_TEXTURE_H__