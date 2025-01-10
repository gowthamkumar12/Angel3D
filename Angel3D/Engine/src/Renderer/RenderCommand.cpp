#include "Renderer/RenderCommand.h"

namespace Engine::Renderer
{
  Engine::Core::Scope<RendererAPI> RenderCommand::s_RendererAPI
                                    = RendererAPI::Create();
} // namespace Engine::Renderer
