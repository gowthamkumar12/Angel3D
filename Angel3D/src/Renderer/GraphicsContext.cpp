#include "Renderer/GraphicsContext.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Angel3D::Renderer
{
	Angel3D::Core::Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:    ANGEL3D_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OPENGL:  return Angel3D::Core::CreateScope<Angel3D::Platform::OpenGL::OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		ANGEL3D_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}