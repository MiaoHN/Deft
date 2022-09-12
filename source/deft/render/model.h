#ifndef __DEFT_MODEL_H__
#define __DEFT_MODEL_H__

#include <memory>
#include <vector>

#include "render/mesh.h"
#include "render/texture.h"

namespace deft {

class Model {
 public:
  Model(const std::shared_ptr<Mesh>&    mesh,
        const std::shared_ptr<Texture>& texture);
  Model(const std::shared_ptr<Mesh>&                 mesh,
        const std::vector<std::shared_ptr<Texture>>& textures);
  ~Model();

  std::shared_ptr<Mesh>&                 getMesh();
  std::vector<std::shared_ptr<Texture>>& getTextures();

  static std::shared_ptr<Model> Create(const std::shared_ptr<Mesh>&    mesh,
                                       const std::shared_ptr<Texture>& texture);
  static std::shared_ptr<Model> Create(
      const std::shared_ptr<Mesh>&                 mesh,
      const std::vector<std::shared_ptr<Texture>>& textures);

 private:
  std::shared_ptr<Mesh> _mesh;

  std::vector<std::shared_ptr<Texture>> _textures;
};

}  // namespace deft

#endif  // __DEFT_MODEL_H__