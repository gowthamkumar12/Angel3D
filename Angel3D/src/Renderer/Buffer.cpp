#include "Core/Log.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Angel3D::Renderer
{
  /**
   * VertexBuffer Class
   */
  VertexBuffer* VertexBuffer::Create(float* f_Vertices, uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::OPENGL:
        return new Angel3D::Platform::OpenGL::OpenGLVertexBuffer(f_Vertices, f_size);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  /**
   * IndexBuffer Class
   */
  IndexBuffer* IndexBuffer::Create(uint32_t* f_Indices, uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::OPENGL:
        return new Angel3D::Platform::OpenGL::OpenGLIndexBuffer(f_Indices, f_size);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }
} // namespace Angel3D::Renderer
