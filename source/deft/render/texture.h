#ifndef __DEFT_TEXTURE_H__
#define __DEFT_TEXTURE_H__

#include <memory>
#include <string>

namespace deft {

class Texture {
 public:
  Texture(int width, int height);
  Texture(const std::string& path);
  ~Texture();

  unsigned int getId();

  void bind(int slot = 0) const;
  void unBind(int slot = 0) const;

  static std::shared_ptr<Texture> Create(int width, int height);
  static std::shared_ptr<Texture> Create(const std::string& path);

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_TEXTURE_H__