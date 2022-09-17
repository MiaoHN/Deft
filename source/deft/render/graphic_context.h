#ifndef __DEFT_GRAPHIC_CONTEXT_H__
#define __DEFT_GRAPHIC_CONTEXT_H__

namespace deft {

class GraphicContext {
 public:
  virtual ~GraphicContext() = default;

  virtual void init() = 0;

  virtual void swapBuffers() = 0;

  static std::unique_ptr<GraphicContext> Create(void* handler);
};

}  // namespace deft

#endif  // __DEFT_GRAPHIC_CONTEXT_H__