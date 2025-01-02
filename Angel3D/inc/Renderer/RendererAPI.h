#pragma once

#include "Renderer/VertexArray.h"
#include "glm/glm.hpp"

namespace Angel3D::Renderer
{
  class RendererAPI
  {
    public:
      enum class API
      {
        NONE = 0,
        OPENGL = 1,
        VULKAN = 2,
        DIRECT3D = 3
      };

      virtual void Init() = 0;

      virtual void SetViewport(uint32_t x, uint32_t y, uint32_t f_width, uint32_t f_height) = 0;

      virtual void SetClearColor(const glm::vec4& f_color) = 0;
      virtual void Clear() = 0;

      virtual void DrawIndexed(const Angel3D::Core::Ref<VertexArray>& f_vertexArray) = 0;

      inline static API GetAPI() { return s_API; }

      static Angel3D::Core::Scope<RendererAPI> Create();

    private:
      static API s_API;
  };
} // namespace Angel3D::Renderer
