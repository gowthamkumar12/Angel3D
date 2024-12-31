#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Ref<VertexArray> VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLVertexArray>();

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

} // namespace Angel3D::Renderer