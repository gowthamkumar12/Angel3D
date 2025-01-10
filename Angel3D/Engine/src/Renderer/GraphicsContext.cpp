#include "Renderer/GraphicsContext.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine::Renderer
{
	Engine::Core::Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OPENGL:  return Engine::Core::CreateScope<Engine::Platform::OpenGL::OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}