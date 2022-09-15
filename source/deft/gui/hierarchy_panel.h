#ifndef __DEFT_HIERARCHY_PANEL_H__
#define __DEFT_HIERARCHY_PANEL_H__

#include "ecs/ecs.h"

namespace deft {

class HierarchyPanel {
 public:
  HierarchyPanel();
  ~HierarchyPanel();

  void update();

  Entity* getSelectedEntity();
  bool    haveSelectedEntity();

 private:
  Entity* _selectedEntity;
  bool   _selected = false;
};

}  // namespace deft

#endif  // __DEFT_HIERARCHY_PANEL_H__