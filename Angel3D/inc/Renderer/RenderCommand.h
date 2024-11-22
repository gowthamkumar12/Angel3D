#pragma once

#include "Renderer/RendererAPI.h"

namespace Angel3D::Renderer
{
  class RenderCommand
  {
    public:
      inline static void SetClearColor(const glm::vec4& f_color)
      {
        s_RendererAPI->SetClearColor(f_color);
      }

      inline static void Clear()
      {
        s_RendererAPI->Clear();
      };

      inline static void DrawIndexed(const std::shared_ptr<VertexArray>& f_vertexArray)
      {
        s_RendererAPI->DrawIndexed(f_vertexArray);
      }

    private:
      static RendererAPI* s_RendererAPI;
  };
} // namespace Angel3D::Renderer
