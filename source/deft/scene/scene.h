#ifndef __DEFT_SCENE_H__
#define __DEFT_SCENE_H__

#include <memory>

#include "render/model.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/texture.h"

namespace deft {

class Scene {
 public:
  Scene();
  ~Scene();

  void tick(float dt);
  void render(Renderer& render);

 private:
  std::vector<std::shared_ptr<Model>> _models;

  std::shared_ptr<Texture> _texture;
  std::shared_ptr<Texture> _floorTexture;
  std::shared_ptr<Shader>  _shader;
};

}  // namespace deft

#endif  // __DEFT_SCENE_H__