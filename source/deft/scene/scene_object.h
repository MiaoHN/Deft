#ifndef __DEFT_SCENE_OBJECT_H__
#define __DEFT_SCENE_OBJECT_H__

#include <memory>

#include "components/transform.h"
#include "render/model.h"

namespace deft {

class SceneObject {
 public:
  SceneObject(const std::shared_ptr<Model>&     model,
              const std::shared_ptr<Transform>& transform);
  ~SceneObject();

  std::shared_ptr<Model>&     getModel();
  std::shared_ptr<Transform>& getTransform();

 private:
  std::shared_ptr<Model> _model;

  std::shared_ptr<Transform> _transform;
};

}  // namespace deft

#endif  // __DEFT_SCENE_OBJECT_H__