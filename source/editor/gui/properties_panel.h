#ifndef __DEFT_PROPERTIES_PANEL_H__
#define __DEFT_PROPERTIES_PANEL_H__

#include <memory>

#include "deft.h"
#include "ecs/ecs.h"
#include "gui/hierarchy_panel.h"

namespace deft {

class PropertiesPanel {
 public:
  PropertiesPanel(Registry* registry);
  ~PropertiesPanel();

  void update(const std::shared_ptr<HierarchyPanel>& hierarchyPanel);

 private:
  void showTransform(Entity entity);
  void showMesh(Entity entity);
  void showLight(Entity entity);

  Registry* _registry;
};

}  // namespace deft

#endif  //__DEFT_PROPERTIES_PANEL_H__