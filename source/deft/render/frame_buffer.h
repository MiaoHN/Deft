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
  virtual ~FrameBuffer() = default;

  virtual void bind() const   = 0;
  virtual void unBind() const = 0;

  virtual unsigned int getColorAttachment() = 0;

  static std::shared_ptr<FrameBuffer> Create(const FrameBufferData& data);
};

}  // namespace deft

#endif  // __DEFT_FRAME_BUFFER_H__