#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Core/Log.h"

#include "glad/glad.h"

namespace Engine::Platform::OpenGL
{
  static GLenum ShaderDataTypeToOpenGLBaseType(Engine::Renderer::ShaderDataType type)
	{
		switch(type)
    {
      case Engine::Renderer::ShaderDataType::Int:     return GL_INT;
      case Engine::Renderer::ShaderDataType::Int2:    return GL_INT;
      case Engine::Renderer::ShaderDataType::Int3:    return GL_INT;
      case Engine::Renderer::ShaderDataType::Int4:    return GL_INT;
      case Engine::Renderer::ShaderDataType::Float:   return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Float2:  return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Float3:  return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Float4:  return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Mat3:    return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Mat4:    return GL_FLOAT;
      case Engine::Renderer::ShaderDataType::Bool:    return GL_BOOL;
    }

		CORE_ASSERT(false, "Unknown shader data type");
    return 0;
	}

  OpenGLVertexArray::OpenGLVertexArray()
  {
    PROFILE_FUNCTION();

    glCreateVertexArrays(1, &m_RendererID);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    PROFILE_FUNCTION();

    glDeleteVertexArrays(1, &m_RendererID);
  }

  void OpenGLVertexArray::Bind() const
  {
    PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
  }

  void OpenGLVertexArray::Unbind() const
  {
    PROFILE_FUNCTION();

    glBindVertexArray(0);
  }

  void OpenGLVertexArray::AddVertexBuffer(const Engine::Core::Ref<Engine::Renderer::VertexBuffer> &f_vertexBuffer)
  {
    PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
    f_vertexBuffer->Bind();

    CORE_ASSERT(f_vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    uint32_t index= 0;
		const auto& layout = f_vertexBuffer->GetLayout();
		for(const auto& element : layout)
		{
      switch (element.Type)
			{
				case Engine::Renderer::ShaderDataType::Float  :
				case Engine::Renderer::ShaderDataType::Float2 :
				case Engine::Renderer::ShaderDataType::Float3 :
				case Engine::Renderer::ShaderDataType::Float4 :
				case Engine::Renderer::ShaderDataType::Int    :
				case Engine::Renderer::ShaderDataType::Int2   :
				case Engine::Renderer::ShaderDataType::Int3   :
				case Engine::Renderer::ShaderDataType::Int4   :
				case Engine::Renderer::ShaderDataType::Bool   :
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(),
                                ShaderDataTypeToOpenGLBaseType(element.Type),
                                element.Normalized ? GL_TRUE : GL_FALSE,
                                layout.GetStride(), (const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}

				case Engine::Renderer::ShaderDataType::Mat3:
				case Engine::Renderer::ShaderDataType::Mat4:
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
					CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

    m_VertexBuffers.push_back(f_vertexBuffer);
  }

  void OpenGLVertexArray::SetIndexBuffer(const Engine::Core::Ref<Engine::Renderer::IndexBuffer> &f_indexBuffer)
  {
    PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
    f_indexBuffer->Bind();

    m_IndexBuffer = f_indexBuffer;
  }
} // namespace Engine::Platform::OpenGL
