#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Angel3D::Renderer
{
  RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;

  Angel3D::Core::Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::NONE:    ANGEL3D_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OPENGL:  return Angel3D::Core::CreateScope<Angel3D::Platform::OpenGL::OpenGLRendererAPI>();
		}
		ANGEL3D_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
} // namespace Angel3D::Renderer
