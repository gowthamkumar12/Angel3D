#pragma once

#include "Renderer/Buffer.h"

namespace Angel3D::Platform::OpenGL
{
  /***
   * OpenGLVertexBuffer Class
   */
  class OpenGLVertexBuffer : public Angel3D::Renderer::VertexBuffer
  {
    public:
      OpenGLVertexBuffer(float* f_Vertices, uint32_t f_size);
      virtual ~OpenGLVertexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;

    private:
      uint32_t m_RendererID;
  };

  /**
   * OpenGLIndexBuffer Class
   */
  class OpenGLIndexBuffer : public Angel3D::Renderer::IndexBuffer
  {
    public:
      OpenGLIndexBuffer(uint32_t* f_Indices, uint32_t f_count);
      virtual ~OpenGLIndexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual uint32_t GetCount() const override;

    private:
      uint32_t m_Count;
      uint32_t m_RendererID;
  };
} // namespace Angel3D::Platform::OpenGL
