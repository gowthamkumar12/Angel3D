#pragma once

#include "Renderer/VertexArray.h"

namespace Angel3D::Platform::OpenGL
{
  class OpenGLVertexArray : public Angel3D::Renderer::VertexArray
  {
    public:
      OpenGLVertexArray();
      virtual ~OpenGLVertexArray();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual void AddVertexBuffer(const std::shared_ptr<Angel3D::Renderer::VertexBuffer>& f_vertexBuffer) override;
      virtual void SetIndexBuffer(const std::shared_ptr<Angel3D::Renderer::IndexBuffer>& f_indexBuffer) override;

      virtual const std::vector<std::shared_ptr<Angel3D::Renderer::VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
      virtual const std::shared_ptr<Angel3D::Renderer::IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
      uint32_t m_RendererID;
      std::vector<std::shared_ptr<Angel3D::Renderer::VertexBuffer>> m_VertexBuffers;
      std::shared_ptr<Angel3D::Renderer::IndexBuffer>  m_IndexBuffer;
  };
} // namespace Angel3D::Platform::OpenGL
