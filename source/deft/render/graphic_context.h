#ifndef __DEFT_GRAPHIC_CONTEXT_H__
#define __DEFT_GRAPHIC_CONTEXT_H__

struct GLFWwindow;

namespace deft {

class GraphicContext {
 public:
  GraphicContext(GLFWwindow* handler);
  ~GraphicContext();

  void swapBuffers();

 private:
  GLFWwindow* _handler;
};

}  // namespace deft

#endif  // __DEFT_GRAPHIC_CONTEXT_H__