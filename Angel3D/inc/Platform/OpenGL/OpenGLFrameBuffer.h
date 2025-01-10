#pragma once

#include "Renderer/FrameBuffer.h"

namespace Angel3D::Platform::OpenGL
{
  class OpenGLFrameBuffer : public Angel3D::Renderer::Framebuffer
  {
    public:
      OpenGLFrameBuffer(const Angel3D::Renderer::FramebufferSpecification& f_specifications);
      virtual ~OpenGLFrameBuffer();

      void Invalidate();
      virtual void Bind() override;
      virtual void Unbind() override;

      virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
      virtual const Angel3D::Renderer::FramebufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
      uint32_t m_RendererID;
      uint32_t m_ColorAttachment, m_DepthAttachment;
      Angel3D::Renderer::FramebufferSpecification m_Specification;
  };
}