#ifndef __DEFT_GUI_H__
#define __DEFT_GUI_H__

#include <memory>

#include "gui/log_panel.h"
#include "gui/menu_bar.h"
#include "gui/scene_panel.h"
#include "scene/scene.h"

namespace deft {

class Gui {
 public:
  Gui();
  ~Gui();

  void init();

  void update();

  void draw();

  bool isScenePanelHovered();

 private:
  void initStyle();

 private:
  std::shared_ptr<LogPanel>   _logPanel;
  std::shared_ptr<ScenePanel> _scenePanel;
  std::shared_ptr<MenuBar>    _menuBar;
};

}  // namespace deft

#endif  // __DEFT_GUI_H__