#include "Core/Log.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine::Renderer
{
  /**
   * VertexBuffer Class
   */
  Engine::Core::Ref<VertexBuffer> VertexBuffer::Create(uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLVertexBuffer>(f_size);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Engine::Core::Ref<VertexBuffer> VertexBuffer::Create(float* f_Vertices, uint32_t f_size)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLVertexBuffer>(f_Vertices, f_size);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  /**
   * IndexBuffer Class
   */
  Engine::Core::Ref<IndexBuffer> IndexBuffer::Create(uint32_t* f_Indices, uint32_t f_count)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLIndexBuffer>(f_Indices, f_count);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }
} // namespace Engine::Renderer
