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
    ANGEL3D_PROFILE_FUNCTION();

    glCreateVertexArrays(1, &m_RendererID);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    ANGEL3D_PROFILE_FUNCTION();

    glDeleteVertexArrays(1, &m_RendererID);
  }

  void OpenGLVertexArray::Bind() const
  {
    ANGEL3D_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
  }

  void OpenGLVertexArray::Unbind() const
  {
    ANGEL3D_PROFILE_FUNCTION();

    glBindVertexArray(0);
  }

  void OpenGLVertexArray::AddVertexBuffer(const Angel3D::Core::Ref<Angel3D::Renderer::VertexBuffer> &f_vertexBuffer)
  {
    ANGEL3D_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
    f_vertexBuffer->Bind();

    ANGEL3D_CORE_ASSERT(f_vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    uint32_t index= 0;
		const auto& layout = f_vertexBuffer->GetLayout();
		for(const auto& element : layout)
		{
      switch (element.Type)
			{
				case Angel3D::Renderer::ShaderDataType::Float  :
				case Angel3D::Renderer::ShaderDataType::Float2 :
				case Angel3D::Renderer::ShaderDataType::Float3 :
				case Angel3D::Renderer::ShaderDataType::Float4 :
				case Angel3D::Renderer::ShaderDataType::Int    :
				case Angel3D::Renderer::ShaderDataType::Int2   :
				case Angel3D::Renderer::ShaderDataType::Int3   :
				case Angel3D::Renderer::ShaderDataType::Int4   :
				case Angel3D::Renderer::ShaderDataType::Bool   :
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                layout.GetStride(), (const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}

				case Angel3D::Renderer::ShaderDataType::Mat3:
				case Angel3D::Renderer::ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex, count,
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(), (const void*)(sizeof(float) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					ANGEL3D_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

    m_VertexBuffers.push_back(f_vertexBuffer);
  }

  void OpenGLVertexArray::SetIndexBuffer(const Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> &f_indexBuffer)
  {
    ANGEL3D_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
    f_indexBuffer->Bind();

    m_IndexBuffer = f_indexBuffer;
  }
} // namespace Angel3D::Platform::OpenGL
