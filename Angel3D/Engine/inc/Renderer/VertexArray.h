#pragma once

#include "Renderer/Buffer.h"

namespace Engine::Renderer
{
  class VertexArray
  {
    public:
      virtual ~VertexArray() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void AddVertexBuffer(const Engine::Core::Ref<VertexBuffer>& f_vertexBuffer) = 0;
      virtual void SetIndexBuffer(const Engine::Core::Ref<IndexBuffer>& f_indexBuffer) = 0;

      virtual const std::vector<Engine::Core::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
      virtual const Engine::Core::Ref<IndexBuffer> GetIndexBuffer() const = 0;

      static Engine::Core::Ref<VertexArray> Create();
  };
} // namespace Engine::Renderer
