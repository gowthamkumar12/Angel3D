#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox
{
  Sandbox2D::Sandbox2D()
  : Angel3D::Core::Layer("Sandbox3D"),
	  m_CameraController(1920.0f / 1080.0f)
  {}

  void Sandbox2D::OnAttach()
  {
    ANGEL3D_PROFILE_FUNCTION();

    m_Texture = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");
  }

  void Sandbox2D::OnDetach()
  {
    ANGEL3D_PROFILE_FUNCTION();
  }

  void Sandbox2D::OnUpdate(Angel3D::Core::Timestep f_ts)
  {
    ANGEL3D_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(f_ts);

    {
      // Render
      ANGEL3D_PROFILE_SCOPE("Renderer Preparation");
      Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
      Angel3D::Renderer::RenderCommand::Clear();
    }

    {
      ANGEL3D_PROFILE_SCOPE("Renderer Draw");
      Angel3D::Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());
      Angel3D::Renderer::Renderer2D::DrawRotatedQuad({-0.5f, -0.25f}, {1.0f, 1.0f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
      Angel3D::Renderer::Renderer2D::DrawQuad({0.5f, -0.25f}, {0.5f, 0.5f}, {0.2f, 0.3f, 0.8f, 1.0f});
      Angel3D::Renderer::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_Texture, 10.0f);
      Angel3D::Renderer::Renderer2D::EndScene();
    }
  }

  void Sandbox2D::OnImGuiRender()
  {
    ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_tileSquareColor));
		ImGui::End();
  }

  void Sandbox2D::OnEvent(Angel3D::Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Sandbox
