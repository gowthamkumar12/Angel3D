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

      virtual void SetClearColor(const glm::vec4& f_color) = 0;
      virtual void Clear() = 0;

      virtual void DrawIndexed(const std::shared_ptr<VertexArray>& f_vertexArray) = 0;

      inline static API GetAPI() { return s_API; }

    private:
      static API s_API;
  };
} // namespace Angel3D::Renderer
