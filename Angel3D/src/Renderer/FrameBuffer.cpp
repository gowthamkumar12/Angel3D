#include "Renderer/FrameBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& f_specifications)
	{
		switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return Angel3D::Core::CreateRef<Angel3D::Platform::OpenGL::OpenGLFrameBuffer>(f_specifications);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
	}
} // namespace Angel3D::Renderer
