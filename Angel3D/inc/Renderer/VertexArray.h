#pragma once

#include "Renderer/Buffer.h"

namespace Angel3D::Renderer
{
  class VertexArray
  {
    public:
      virtual ~VertexArray() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void AddVertexBuffer(const Angel3D::Core::Ref<VertexBuffer>& f_vertexBuffer) = 0;
      virtual void SetIndexBuffer(const Angel3D::Core::Ref<IndexBuffer>& f_indexBuffer) = 0;

      virtual const std::vector<Angel3D::Core::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
      virtual const Angel3D::Core::Ref<IndexBuffer> GetIndexBuffer() const = 0;

      static Angel3D::Core::Ref<VertexArray> Create();
  };
} // namespace Angel3D::Renderer
