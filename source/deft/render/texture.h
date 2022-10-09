#ifndef __DEFT_TEXTURE_H__
#define __DEFT_TEXTURE_H__

#include <memory>
#include <string>

#include "core/math/math.h"

namespace deft {

class Texture {
 public:
  virtual ~Texture() = default;

  virtual unsigned int getId() = 0;

  virtual void bind(int slot = 0) const   = 0;
  virtual void unBind(int slot = 0) const = 0;

  virtual void setData(void* data, int size) = 0;

  static std::shared_ptr<Texture> Create(int width, int height);
  static std::shared_ptr<Texture> Create(const std::string& path);
};

}  // namespace deft

#endif  // __DEFT_TEXTURE_H__