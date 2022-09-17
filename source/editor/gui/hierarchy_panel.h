#ifndef __DEFT_HIERARCHY_PANEL_H__
#define __DEFT_HIERARCHY_PANEL_H__

#include "deft.h"

namespace deft {

class HierarchyPanel {
 public:
  HierarchyPanel(Registry* registry);
  ~HierarchyPanel();

  void update();

  Entity getSelectedEntity();
  bool   haveSelectedEntity();

 private:
  Entity    _selectedEntity;
  Registry* _registry;
  bool      _selected = false;
};

}  // namespace deft

#endif  // __DEFT_HIERARCHY_PANEL_H__