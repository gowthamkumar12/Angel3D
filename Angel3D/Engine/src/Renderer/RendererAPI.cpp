#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine::Renderer
{
  RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;

  Engine::Core::Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::NONE:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OPENGL:  return Engine::Core::CreateScope<Engine::Platform::OpenGL::OpenGLRendererAPI>();
		}
		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
} // namespace Engine::Renderer
