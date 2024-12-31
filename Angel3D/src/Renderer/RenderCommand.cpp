#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Scope<RendererAPI> RenderCommand::s_RendererAPI
                                    = Angel3D::Core::CreateScope<Angel3D::Platform::OpenGL::OpenGLRendererAPI>();
} // namespace Angel3D::Renderer
