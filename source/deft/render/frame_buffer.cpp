#include "render/frame_buffer.h"

#include "pch.h"
#include "platform/render/opengl/opengl_frame_buffer.h"
#include "render/render_api.h"

namespace deft {

std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferData& data) {
  switch (RenderAPI::Get()) {
    case RenderAPI::OpenGL:
      return std::make_shared<OpenGLFrameBuffer>(data);
    default:
      LOG_CORE_FATAL("RenderAPI is not specified!");
      exit(-1);
  }
  return nullptr;
}

}  // namespace deft
