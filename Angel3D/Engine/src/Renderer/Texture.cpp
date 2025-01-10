#include "Core/Log.h"

#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine::Renderer
{
  /**
   * Texture2D Class
   */
  Engine::Core::Ref<Texture2D> Texture2D::Create(uint32_t f_width, uint32_t f_height)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLTexture2D>(f_width, f_height);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Engine::Core::Ref<Texture2D> Texture2D::Create(const std::string& f_filePath)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLTexture2D>(f_filePath);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }
} // namespace Engine::Renderer
