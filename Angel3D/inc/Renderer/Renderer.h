#pragma once

#include "Renderer/RenderCommand.h"

namespace Angel3D::Renderer
{
  class Renderer
  {
    public:
      static void BeginScene();
      static void EndScene();

      static void Submit(const std::shared_ptr<VertexArray>& f_vertexArray);

      inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
  };
} // namespace Angel3D::Renderer
