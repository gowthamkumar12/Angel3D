#include "Renderer/RenderCommand.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Scope<RendererAPI> RenderCommand::s_RendererAPI
                                    = RendererAPI::Create();
} // namespace Angel3D::Renderer
