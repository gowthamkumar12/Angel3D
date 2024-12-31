#include "Core/Log.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Angel3D::Renderer
{
  /**
   * VertexBuffer Class
   */
  Angel3D::Core::Ref<VertexBuffer> VertexBuffer::Create(float* f_Vertices, uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLVertexBuffer>(f_Vertices, f_size);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  /**
   * IndexBuffer Class
   */
  Angel3D::Core::Ref<IndexBuffer> IndexBuffer::Create(uint32_t* f_Indices, uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLIndexBuffer>(f_Indices, f_size);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }
} // namespace Angel3D::Renderer
