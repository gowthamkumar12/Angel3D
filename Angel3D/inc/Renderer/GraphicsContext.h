#pragma once

#include "Core/Core.h"

namespace Angel3D::Renderer
{
  class GraphicsContext
  {
    public:
      virtual void Init() = 0;
      virtual void SwapBuffers() = 0;

      static Angel3D::Core::Scope<GraphicsContext> Create(void* window);
  };
} // namespace Angel3D::Renderer
