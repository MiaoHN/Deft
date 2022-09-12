#ifndef __DEFT_SCENE_OBJECT_H__
#define __DEFT_SCENE_OBJECT_H__

#include <memory>

#include "components/component.h"
#include "ecs/ecs.h"
#include "render/model.h"

namespace deft {

class SceneObject {
 public:
  SceneObject(const std::shared_ptr<Model>& model, const Transform& transform,
              bool isLight = false);
  ~SceneObject();

  Entity& getEntityId();

  std::shared_ptr<Model>& getModel();
  Transform&              getTransform();

  void setLight(bool flag);
  bool isLight();

 private:
  Entity _entityId;

  std::shared_ptr<Model> _model;
};

}  // namespace deft

#endif  // __DEFT_SCENE_OBJECT_H__