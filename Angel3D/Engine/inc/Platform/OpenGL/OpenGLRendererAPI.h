#pragma once

#include "Renderer/RendererAPI.h"

namespace Engine::Platform::OpenGL
{
  class OpenGLRendererAPI : public Engine::Renderer::RendererAPI
  {
    public:
      virtual void Init() override;
      virtual void SetViewport(uint32_t x, uint32_t y, uint32_t f_width, uint32_t f_height) override;

      virtual void SetClearColor(const glm::vec4& f_color) override;
      virtual void Clear() override;

      virtual void DrawIndexed(const Engine::Core::Ref<Engine::Renderer::VertexArray>& f_vertexArray, uint32_t f_count = 0) override;
  };
} // namespace Engine::Platform::OpenGL