#pragma once

namespace Angel3D::Renderer
{
  class GraphicsContext
  {
    public:
      virtual void Init() = 0;
      virtual void SwapBuffers() = 0;
  };
} // namespace Angel3D::Renderer
