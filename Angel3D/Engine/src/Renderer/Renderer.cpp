#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"

namespace Engine::Renderer
{
  Engine::Core::Scope<Renderer::SceneData> Renderer::s_SceneData = Engine::Core::CreateScope<Renderer::SceneData>();

  void Renderer::Init()
  {
    PROFILE_FUNCTION();

    RenderCommand::Init();
    Renderer2D::Init();
  }

  void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

  void Renderer::OnWindowResize(uint32_t f_width, uint32_t f_height)
  {
    RenderCommand::SetViewport(0, 0, f_width, f_height);
  }

  void Renderer::BeginScene(Engine::Renderer::OrthographicCamera& f_camera)
  {
    s_SceneData->m_ViewProjectionMatrix = f_camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const Engine::Core::Ref<Shader>&      f_Shader,
                        const Engine::Core::Ref<VertexArray>& f_vertexArray,
                        const glm::mat4&                       f_transform)
  {
    f_Shader->Bind();
    f_Shader->SetMat4("u_ViewProjectionMatrix", s_SceneData->m_ViewProjectionMatrix);
    f_Shader->SetMat4("u_Transform", f_transform);

    f_vertexArray->Bind();
    RenderCommand::DrawIndexed(f_vertexArray);
  }
} // namespace Engine::Renderer
