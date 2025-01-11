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

      virtual void Resize(uint32_t f_width, uint32_t f_height) override;

      virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
      virtual const Engine::Renderer::FramebufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
      uint32_t m_RendererID = 0;
      uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
      Engine::Renderer::FramebufferSpecification m_Specification;
  };
}