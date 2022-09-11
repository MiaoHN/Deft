#ifndef __DEFT_TEXTURE_H__
#define __DEFT_TEXTURE_H__

#include <memory>
#include <string>

#include "math/math.h"

namespace deft {

class Texture {
 public:
  Texture(int width, int height);
  Texture(const math::Vector3& color);
  Texture(const std::string& path);
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

  void           setColor(const math::Vector3& color);
  math::Vector3& getColor();

  static std::shared_ptr<Texture> Create(int width, int height);
  static std::shared_ptr<Texture> Create(const math::Vector3& color);
  static std::shared_ptr<Texture> Create(const std::string& path);

 private:
  unsigned int _id;

  DataType      _dataType;
  math::Vector3 _color;
};

}  // namespace deft

#endif  // __DEFT_TEXTURE_H__