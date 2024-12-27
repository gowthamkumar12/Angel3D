#pragma once

#include "Renderer/RendererAPI.h"

namespace Angel3D::Platform::OpenGL
{
  class OpenGLRendererAPI : public Angel3D::Renderer::RendererAPI
  {
    public:
      virtual void Init() override;
      virtual void SetClearColor(const glm::vec4& f_color) override;
      virtual void Clear() override;

      virtual void DrawIndexed(const Angel3D::Core::Ref<Angel3D::Renderer::VertexArray>& f_vertexArray) override;
  };
} // namespace Angel3D::Platform::OpenGL