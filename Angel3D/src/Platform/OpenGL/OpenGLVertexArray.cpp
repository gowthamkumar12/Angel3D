#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Core/Log.h"

#include "glad/glad.h"

namespace Angel3D::Platform::OpenGL
{
  static GLenum ShaderDataTypeToOpenGLBaseType(Angel3D::Renderer::ShaderDataType type)
	{
		switch(type)
    {
      case Angel3D::Renderer::ShaderDataType::Int:     return GL_INT;
      case Angel3D::Renderer::ShaderDataType::Int2:    return GL_INT;
      case Angel3D::Renderer::ShaderDataType::Int3:    return GL_INT;
      case Angel3D::Renderer::ShaderDataType::Int4:    return GL_INT;
      case Angel3D::Renderer::ShaderDataType::Float:   return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Float2:  return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Float3:  return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Float4:  return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Mat3:    return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Mat4:    return GL_FLOAT;
      case Angel3D::Renderer::ShaderDataType::Bool:    return GL_BOOL;
    }

		ANGEL3D_CORE_ASSERT(false, "Unknown shader data type");
    return 0;
	}

  OpenGLVertexArray::OpenGLVertexArray()
  {
    glCreateVertexArrays(1, &m_RendererID);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_RendererID);
  }

  void OpenGLVertexArray::Bind() const
  {
    glBindVertexArray(m_RendererID);
  }

  void OpenGLVertexArray::Unbind() const
  {
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<Angel3D::Renderer::VertexBuffer> &f_vertexBuffer)
  {
    glBindVertexArray(m_RendererID);
    f_vertexBuffer->Bind();

    ANGEL3D_CORE_ASSERT(f_vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    uint32_t index= 0;
		const auto& layout = f_vertexBuffer->GetLayout();
		for(const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(element.Type),
			                      element.Normalized ? GL_TRUE : GL_FALSE,
			                      layout.GetStride(), (const void*)element.Offset);
			index++;
		}

    m_VertexBuffers.push_back(f_vertexBuffer);
  }

  void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<Angel3D::Renderer::IndexBuffer> &f_indexBuffer)
  {
    glBindVertexArray(m_RendererID);
    f_indexBuffer->Bind();

    m_IndexBuffer = f_indexBuffer;
  }
} // namespace Angel3D::Platform::OpenGL
