#ifndef __DEFT_SCENE_H__
#define __DEFT_SCENE_H__

#include <memory>

#include "render/frame_buffer.h"
#include "render/mesh.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/texture.h"
#include "scene/scene_object.h"

namespace deft {

class Scene {
 public:
  Scene();
  ~Scene();

  void tick(float dt);
  void render(Renderer& render);

  std::shared_ptr<FrameBuffer>& getFrameBuffer();

 private:
  std::vector<std::shared_ptr<SceneObject>> _boxObjects;

  std::vector<std::shared_ptr<SceneObject>> _objects;

  std::vector<std::shared_ptr<SceneObject>> _lightObjects;

  std::shared_ptr<Shader>      _boxShader;
  std::shared_ptr<Shader>      _lightShader;
  std::shared_ptr<FrameBuffer> _frameBuffer;
};

}  // namespace deft

#endif  // __DEFT_SCENE_H__