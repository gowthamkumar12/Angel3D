#include "Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"

namespace Angel3D::Platform::OpenGL
{
  /**
   * OpenGLVertexBuffer Class
   */
  OpenGLVertexBuffer::OpenGLVertexBuffer(float* f_Vertices, uint32_t f_size)
  {
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, f_size, f_Vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLVertexBuffer::Bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  }

  void OpenGLVertexBuffer::Unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  /**
   * OpenGLIndexBuffer Class
   */
  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *f_Indices, uint32_t f_count)
  : m_Count(f_count)
  {
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, f_count * sizeof(uint32_t), f_Indices, GL_STATIC_DRAW);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLIndexBuffer::Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  }

  void OpenGLIndexBuffer::Unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  uint32_t OpenGLIndexBuffer::GetCount() const
  {
    return m_Count;
  }

  } // namespace Angel3D::Platform::OpenGL