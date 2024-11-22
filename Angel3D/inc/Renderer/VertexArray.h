#pragma once

#include "Renderer/Buffer.h"

namespace Angel3D::Renderer
{
  class VertexArray
  {
    public:
      virtual ~VertexArray() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& f_vertexBuffer) = 0;
      virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& f_indexBuffer) = 0;

      virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
      virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

      static VertexArray* Create();
  };
} // namespace Angel3D::Renderer
