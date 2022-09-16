#ifndef __DEFT_SCENE_PANEL_H__
#define __DEFT_SCENE_PANEL_H__

#include <memory>

#include "deft.h"
#include "scene/scene.h"

namespace deft {

class ScenePanel {
 public:
  ScenePanel(Registry* registry);
  ~ScenePanel();

  void update(std::shared_ptr<FrameBuffer> buffer);

  bool isHovered();

 private:
  std::shared_ptr<Scene> _scene;
  math::Vector2          _sceneSize;

  bool _isHovered;

  Registry* _registry;
};

}  // namespace deft

#endif  // __DEFT_SCENE_PANEL_H__