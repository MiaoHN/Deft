#ifndef __DEFT_TEXTURE_H__
#define __DEFT_TEXTURE_H__

#include <memory>
#include <string>

#include "math/math.h"

namespace deft {

enum class TextureType {
  Diffuse,
  Specular,
};

class Texture {
 public:
  Texture(int width, int height, TextureType type = TextureType::Diffuse);
  Texture(const math::Vector3& color, TextureType type = TextureType::Diffuse);
  Texture(const std::string& path, TextureType type = TextureType::Diffuse);
  ~Texture();

  unsigned int getId();

  void bind(int slot = 0) const;
  void unBind(int slot = 0) const;

  enum DataType {
    Blank,
    Image,
    Color,
  };

  DataType getDataType();

  TextureType getType();
  void        setType(TextureType type);

  void           setColor(const math::Vector3& color);
  math::Vector3& getColor();

  static std::shared_ptr<Texture> Create(
      int width, int height, TextureType type = TextureType::Diffuse);
  static std::shared_ptr<Texture> Create(
      const math::Vector3& color, TextureType type = TextureType::Diffuse);
  static std::shared_ptr<Texture> Create(
      const std::string& path, TextureType type = TextureType::Diffuse);

 private:
  unsigned int _id;

  DataType      _dataType;
  TextureType   _type;
  math::Vector3 _color;
};

}  // namespace deft

#endif  // __DEFT_TEXTURE_H__