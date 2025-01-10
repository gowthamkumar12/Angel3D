#pragma once

#include "Renderer/Buffer.h"

namespace Engine::Platform::OpenGL
{
  /***
   * OpenGLVertexBuffer Class
   */
  class OpenGLVertexBuffer : public Engine::Renderer::VertexBuffer
  {
    public:
      OpenGLVertexBuffer(uint32_t f_size);
      OpenGLVertexBuffer(float* f_Vertices, uint32_t f_size);
      virtual ~OpenGLVertexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual void SetData(const void* data, uint32_t size) override;

      virtual const Engine::Renderer::BufferLayout& GetLayout() const override { return m_Layout; }
      virtual void SetLayout(const Engine::Renderer::BufferLayout& f_layout) override { m_Layout = f_layout; }
    private:
      uint32_t m_RendererID;
      Engine::Renderer::BufferLayout m_Layout;
  };

  /**
   * OpenGLIndexBuffer Class
   */
  class OpenGLIndexBuffer : public Engine::Renderer::IndexBuffer
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
} // namespace Engine::Platform::OpenGL
