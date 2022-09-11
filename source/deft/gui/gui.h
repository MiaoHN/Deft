#ifndef __DEFT_GUI_H__
#define __DEFT_GUI_H__

#include <memory>

#include "gui/log_panel.h"
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

  std::shared_ptr<LogPanel> _logPanel;
};

}  // namespace deft

#endif  // __DEFT_GUI_H__