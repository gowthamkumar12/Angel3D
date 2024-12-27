#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Ref<Shader> Shader::Create(const std::string& f_filePath)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Angel3D::Platform::OpenGL::OpenGLShader>(f_filePath);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Angel3D::Core::Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragSrc)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Angel3D::Platform::OpenGL::OpenGLShader>(vertexSrc, fragSrc);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

} // namespace Angel3D::Renderer