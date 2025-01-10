#pragma once

#include "Renderer/FrameBuffer.h"

namespace Engine::Platform::OpenGL
{
  class OpenGLFrameBuffer : public Engine::Renderer::Framebuffer
  {
    public:
      OpenGLFrameBuffer(const Engine::Renderer::FramebufferSpecification& f_specifications);
      virtual ~OpenGLFrameBuffer();

      void Invalidate();
      virtual void Bind() override;
      virtual void Unbind() override;

      virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
      virtual const Engine::Renderer::FramebufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
      uint32_t m_RendererID;
      uint32_t m_ColorAttachment, m_DepthAttachment;
      Engine::Renderer::FramebufferSpecification m_Specification;
  };
}