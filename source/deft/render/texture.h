#ifndef __DEFT_TEXTURE_H__
#define __DEFT_TEXTURE_H__

#include <string>

namespace deft {

class Texture {
 public:
  Texture(const std::string& path);
  ~Texture();

  void bind(int slot = 0) const;
  void unBind(int slot = 0) const;

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_TEXTURE_H__