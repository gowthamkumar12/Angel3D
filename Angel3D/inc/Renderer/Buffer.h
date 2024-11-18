#pragma once

namespace Angel3D::Renderer
{
  /**
   * VertexBuffer Class
   */
  class VertexBuffer
  {
    public:
      virtual ~VertexBuffer() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      static VertexBuffer* Create(float* f_Vertices, uint32_t f_size);
  };

  /**
   * IndexBuffer Class
   */
  class IndexBuffer
  {
    public:
      virtual ~IndexBuffer() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual uint32_t GetCount() const = 0;

      static IndexBuffer* Create(uint32_t* f_Indices, uint32_t f_size);
  };
} // namespace Angel3D::Renderer
