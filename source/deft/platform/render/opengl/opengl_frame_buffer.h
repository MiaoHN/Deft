#ifndef __DEFT_OPENGL_FRAME_BUFFER_H__
#define __DEFT_OPENGL_FRAME_BUFFER_H__

#include "render/frame_buffer.h"

namespace deft {

class OpenGLFrameBuffer : public FrameBuffer {
 public:
  OpenGLFrameBuffer(const FrameBufferData& data);
  ~OpenGLFrameBuffer();

  void bind() const override;
  void unBind() const override;

  unsigned int getColorAttachment() override;

 private:
  unsigned int _id;
  unsigned int _rbo;

  unsigned int _colorAttachment;
  unsigned int _depthAttachment;
};

}  // namespace deft

#endif  // __DEFT_OPENGL_FRAME_BUFFER_H__