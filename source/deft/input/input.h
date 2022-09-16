#ifndef __DEFT_INPUT_H__
#define __DEFT_INPUT_H__

#include "input/key_code.h"
#include "input/mouse_button_code.h"
#include "math/math.h"

namespace deft {

class Input {
 public:
  static bool IsMouseButtonPress(MouseButton button);

  static bool IsKeyPress(KeyCode key);

  static math::Vector2 GetMousePosition();
};

}  // namespace deft

#endif  // __DEFT_INPUT_H__