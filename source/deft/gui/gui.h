#ifndef __DEFT_GUI_H__
#define __DEFT_GUI_H__

#include <memory>

#include "scene/scene.h"

namespace deft {

class Gui {
 public:
  Gui();
  ~Gui();

  void init();

  void update();

  void draw();

 private:
  std::shared_ptr<Scene> _scene;
};

}  // namespace deft

#endif  // __DEFT_GUI_H__