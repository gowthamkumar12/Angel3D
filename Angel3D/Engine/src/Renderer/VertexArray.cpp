#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine::Renderer
{
  Engine::Core::Ref<VertexArray> VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLVertexArray>();

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

} // namespace Engine::Renderer