#include "Renderer/FrameBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Engine::Renderer
{
  Engine::Core::Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& f_specifications)
	{
		switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Engine::Core::CreateRef<Engine::Platform::OpenGL::OpenGLFrameBuffer>(f_specifications);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
	}
} // namespace Engine::Renderer
