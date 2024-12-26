#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Angel3D::Renderer
{
  Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragSrc)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return new Angel3D::Platform::OpenGL::OpenGLShader(vertexSrc, fragSrc);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

} // namespace Angel3D::Renderer