#ifndef __DEFT_RENDERER_H__
#define __DEFT_RENDERER_H__

#include <memory>

#include "ecs/ecs.h"
#include "math/math.h"
#include "render/camera.h"
#include "render/frame_buffer.h"
#include "render/mesh.h"
#include "render/model.h"
#include "render/shader.h"
#include "render/texture.h"
#include "scene/scene_object.h"

namespace deft {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void begin(std::shared_ptr<Camera> camera);

  void drawFrame(std::shared_ptr<FrameBuffer>& frameBuffer);

  void drawMesh(const std::shared_ptr<Mesh>&   mesh,
                const std::shared_ptr<Shader>& shader);

  void submit(const std::shared_ptr<Model>&  model,
              const std::shared_ptr<Shader>& shader,
              const math::Vector3&           position);

  void submit(const std::shared_ptr<Mesh>&    mesh,
              const std::shared_ptr<Shader>&  shader,
              const std::shared_ptr<Texture>& texture,
              const math::Vector3&            position);

  void submit(const std::shared_ptr<SceneObject>& object,
              const std::shared_ptr<Shader>&      shader,
              const math::Vector3&                position);

  void addLight(Entity entity);

  void end();

 private:
  math::Matrix4 _proj;
  math::Matrix4 _view;
  math::Vector3 _cameraPos;

  std::vector<Entity> _lights;

  std::shared_ptr<Mesh>   _frameModel;   // tmp
  std::shared_ptr<Shader> _frameShader;  // tmp
};

}  // namespace deft

#endif  // __DEFT_RENDERER_H__