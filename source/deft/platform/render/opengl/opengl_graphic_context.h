#ifndef __DEFT_OPENGL_GRAPHIC_CONTEXT_H__
#define __DEFT_OPENGL_GRAPHIC_CONTEXT_H__

#include "render/graphic_context.h"

struct GLFWwindow;

namespace deft {

class OpenGLGraphicContext : public GraphicContext {
 public:
  OpenGLGraphicContext(void* handler);
  ~OpenGLGraphicContext();

  void init() override;

  void swapBuffers() override;

 private:
  GLFWwindow* _handler;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_GRAPHIC_CONTEXT_H__