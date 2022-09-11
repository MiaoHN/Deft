#ifndef __DEFT_SCENE_PANEL_H__
#define __DEFT_SCENE_PANEL_H__

#include <memory>

#include "scene/scene.h"

namespace deft {

class ScenePanel {
 public:
  ScenePanel();
  ~ScenePanel();

  void update();

 private:
  std::shared_ptr<Scene> _scene;
};

}  // namespace deft

#endif  // __DEFT_SCENE_PANEL_H__