#pragma once

#include "Core/Core.h"

namespace Engine::Renderer
{
  class GraphicsContext
  {
    public:
      virtual void Init() = 0;
      virtual void SwapBuffers() = 0;

      static Engine::Core::Scope<GraphicsContext> Create(void* window);
  };
} // namespace Engine::Renderer
