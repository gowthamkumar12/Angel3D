#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Angel3D::Renderer
{
  void Renderer::BeginScene()
  {
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const std::shared_ptr<VertexArray> &f_vertexArray)
  {
    f_vertexArray->Bind();
    RenderCommand::DrawIndexed(f_vertexArray);
  }
} // namespace Angel3D::Renderer
