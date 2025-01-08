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

    Angel3D::Renderer::Renderer2D::ResetStats();
    {
      // Render
      ANGEL3D_PROFILE_SCOPE("Renderer Preparation");
      Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
      Angel3D::Renderer::RenderCommand::Clear();
    }

    {
      static float rotation = 0.0f;
		  rotation += f_ts * 50.0f;

      ANGEL3D_PROFILE_SCOPE("Renderer Draw");

      /* --- Scene-1 start --- */
      Angel3D::Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());

      // Quads with colors
      Angel3D::Renderer::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
      Angel3D::Renderer::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

      // Quads with colors and textures
      Angel3D::Renderer::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_Texture, 10.0f);

      // Rotated Quads with colors
      Angel3D::Renderer::Renderer2D::DrawRotatedQuad({-0.5f, -0.25f}, {1.0f, 1.0f}, rotation, {0.8f, 0.2f, 0.3f, 1.0f});

      // Rotates Quads with colors and textures
      Angel3D::Renderer::Renderer2D::DrawRotatedQuad({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, m_Texture, 10.0f);

      Angel3D::Renderer::Renderer2D::EndScene();
      /* --- Scene-1 end --- */

      /* --- Scene-2 start --- */
      Angel3D::Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());

      for (float y = -5.0f; y < 5.0f; y += 0.5f)
      {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
          glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
          Angel3D::Renderer::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
        }
      }

      Angel3D::Renderer::Renderer2D::EndScene();
      /* --- Scene-2 end --- */
    }
  }

  void Sandbox2D::OnImGuiRender()
  {
    ImGui::Begin("Statistics");

    auto stats = Angel3D::Renderer::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Statistics");
    ImGui::Text("Draw Calls : %d", stats.DrawCalls);
    ImGui::Text("Quads      : %d", stats.QuadCount);
    ImGui::Text("Vertices   : %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices    : %d", stats.GetTotalIndexCount());

		ImGui::End();
  }

  void Sandbox2D::OnEvent(Angel3D::Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Sandbox
