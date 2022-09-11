#ifndef __DEFT_PROPERTIES_PANEL_H__
#define __DEFT_PROPERTIES_PANEL_H__

#include <memory>

#include "ecs/ecs.h"
#include "gui/hierarchy_panel.h"

namespace deft {

class PropertiesPanel {
 public:
  PropertiesPanel();
  ~PropertiesPanel();

  void update(const std::shared_ptr<HierarchyPanel>& hierarchyPanel);

 private:
  void showTransform(Entity entity);
  void showTexture(Entity entity);
};

}  // namespace deft

#endif  //__DEFT_PROPERTIES_PANEL_H__