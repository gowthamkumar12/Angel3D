#pragma once

#include "Renderer/RendererAPI.h"

namespace Engine::Renderer
{
  class RenderCommand
  {
    public:
      inline static void Init()
      {
        s_RendererAPI->Init();
      }

      inline static void SetViewport(uint32_t x, uint32_t y, uint32_t f_width, uint32_t f_height)
      {
        s_RendererAPI->SetViewport(x, y, f_width, f_height);
      }

      inline static void SetClearColor(const glm::vec4& f_color)
      {
        s_RendererAPI->SetClearColor(f_color);
      }

      inline static void Clear()
      {
        s_RendererAPI->Clear();
      };

      inline static void DrawIndexed(const Engine::Core::Ref<VertexArray>& f_vertexArray, uint32_t f_count = 0)
      {
        s_RendererAPI->DrawIndexed(f_vertexArray, f_count);
      }

    private:
      static Engine::Core::Scope<RendererAPI> s_RendererAPI;
  };
} // namespace Engine::Renderer
