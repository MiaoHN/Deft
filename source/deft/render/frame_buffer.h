#ifndef __DEFT_FRAME_BUFFER_H__
#define __DEFT_FRAME_BUFFER_H__

#include <memory>

#include "render/texture.h"

namespace deft {

struct FrameBufferData {
  int width;
  int height;

  FrameBufferData(int width_, int height_) : width(width_), height(height_) {}
};

class FrameBuffer {
 public:
  FrameBuffer(const FrameBufferData& data);
  ~FrameBuffer();

  void bind() const;
  void unBind() const;

  unsigned int getColorAttachment();

  static std::shared_ptr<FrameBuffer> Create(const FrameBufferData& data);

 private:
  unsigned int _id;
  unsigned int _rbo;

  unsigned int _colorAttachment;
  unsigned int _depthAttachment;
};

}  // namespace deft

#endif  // __DEFT_FRAME_BUFFER_H__