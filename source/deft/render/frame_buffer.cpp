#include "render/frame_buffer.h"

#include <glad/glad.h>

#include "pch.h"

namespace deft {

FrameBuffer::FrameBuffer(const FrameBufferData& data) {
  glGenFramebuffers(1, &_id);
  glBindFramebuffer(GL_FRAMEBUFFER, _id);

  glGenTextures(1, &_colorAttachment);
  glBindTexture(GL_TEXTURE_2D, _colorAttachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         _colorAttachment, 0);

  glGenTextures(1, &_depthAttachment);
  glBindTexture(GL_TEXTURE_2D, _depthAttachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, data.width, data.height, 0,
               GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         _depthAttachment, 0);

  glGenRenderbuffers(1, &_rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, _rbo);

  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, data.width,
                        data.height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, _rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    LOG_CLIENT_ERROR("FrameBuffer::FrameBuffer FrameBuffer is not complete!");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() { glDeleteFramebuffers(1, &_id); }

void FrameBuffer::bind() const { glBindFramebuffer(GL_FRAMEBUFFER, _id); }

void FrameBuffer::unBind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

unsigned int FrameBuffer::getColorAttachment() { return _colorAttachment; }

std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferData& data) {
  return std::make_shared<FrameBuffer>(data);
}

}  // namespace deft
