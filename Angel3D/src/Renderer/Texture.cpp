#include "Core/Log.h"

#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Angel3D::Renderer
{
  /**
   * Texture2D Class
   */
  Angel3D::Core::Ref<Texture2D> Texture2D::Create(uint32_t f_width, uint32_t f_height)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLTexture2D>(f_width, f_height);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Angel3D::Core::Ref<Texture2D> Texture2D::Create(const std::string& f_filePath)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLTexture2D>(f_filePath);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }
} // namespace Angel3D::Renderer
