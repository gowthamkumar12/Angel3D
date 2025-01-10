#pragma once

#include "Renderer/VertexArray.h"

namespace Engine::Platform::OpenGL
{
  class OpenGLVertexArray : public Engine::Renderer::VertexArray
  {
    public:
      OpenGLVertexArray();
      virtual ~OpenGLVertexArray();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual void AddVertexBuffer(const Engine::Core::Ref<Engine::Renderer::VertexBuffer>& f_vertexBuffer) override;
      virtual void SetIndexBuffer(const Engine::Core::Ref<Engine::Renderer::IndexBuffer>& f_indexBuffer) override;

      virtual const std::vector<Engine::Core::Ref<Engine::Renderer::VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
      virtual const Engine::Core::Ref<Engine::Renderer::IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
      uint32_t m_RendererID;
      uint32_t m_VertexBufferIndex = 0;
      std::vector<Engine::Core::Ref<Engine::Renderer::VertexBuffer>> m_VertexBuffers;
      Engine::Core::Ref<Engine::Renderer::IndexBuffer>               m_IndexBuffer;
  };
} // namespace Engine::Platform::OpenGL
