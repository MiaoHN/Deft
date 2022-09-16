#ifndef __DEFT_LAYER_H__
#define __DEFT_LAYER_H__

namespace deft {

class Layer {
 public:
  virtual void update(float dt) = 0;
};

}  // namespace deft

#endif  // __DEFT_LAYER_H__