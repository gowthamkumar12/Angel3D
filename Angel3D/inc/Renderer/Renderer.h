#pragma once

namespace Angel3D::Renderer
{
  enum class RendererAPI
  {
    NONE = 0,
    OPENGL = 1,
    VULKAN = 2,
    DIRECT3D = 3,
  };

  class Renderer
  {
    public:
      inline static RendererAPI GetAPI() { return s_RendererAPI; }
    private:
      static RendererAPI s_RendererAPI;
  };
} // namespace Angel3D::Renderer
