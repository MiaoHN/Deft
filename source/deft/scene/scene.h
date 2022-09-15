#ifndef __DEFT_SCENE_H__
#define __DEFT_SCENE_H__

#include <memory>

#include "ecs/system/render_system.h"
#include "render/frame_buffer.h"
#include "render/mesh.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/texture.h"

namespace deft {

class Scene {
 public:
  Scene();
  ~Scene();

  void updateEditMode(float dt, const std::shared_ptr<Camera>& camera);

  Registry& getRegistry();

 private:
  std::shared_ptr<RenderSystem> _renderSystem;

  Registry _registry;
};

}  // namespace deft

#endif  // __DEFT_SCENE_H__