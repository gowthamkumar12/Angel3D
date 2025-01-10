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

    Angel3D::Renderer::FramebufferSpecification frameBufferSpecs;
    frameBufferSpecs.Width = 1280;
    frameBufferSpecs.Height = 720;
    m_Framebuffer = Angel3D::Renderer::Framebuffer::Create(frameBufferSpecs);
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
      m_Framebuffer->Bind();
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
      m_Framebuffer->Unbind();
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
    static bool dockingEnabled = true;
	  if (dockingEnabled)
    {
      bool                      dockingSpaceOpen = true;
      static bool               opt_fullscreen   = true;
      static bool               opt_padding      = false;
      static ImGuiDockNodeFlags dockspace_flags  = ImGuiDockNodeFlags_None;
      ImGuiWindowFlags          window_flags     = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

      if (opt_fullscreen)
      {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
      }

      if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      {
        window_flags |= ImGuiWindowFlags_NoBackground;
      }

      if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

      ImGui::Begin("DockSpace Demo", &dockingSpaceOpen, window_flags);

      if (!opt_padding)
        ImGui::PopStyleVar();

      if (opt_fullscreen)
        ImGui::PopStyleVar(2);

      // Submit the DockSpace
      ImGuiIO& io = ImGui::GetIO();
      if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
      {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
      }

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("File"))
        {
          if (ImGui::MenuItem("Exit")) Angel3D::Core::Application::Get().Close();
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }

      ImGui::Begin("Statistics");

        auto stats = Angel3D::Renderer::Renderer2D::GetStats();
        ImGui::Text("Renderer2D Statistics");
        ImGui::Text("Draw Calls : %d", stats.DrawCalls);
        ImGui::Text("Quads      : %d", stats.QuadCount);
        ImGui::Text("Vertices   : %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices    : %d", stats.GetTotalIndexCount());

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		    ImGui::Image((unsigned long long)textureID, ImVec2{ 1280, 720 });

      ImGui::End();

      ImGui::End();
    }
    else
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
  }

  void Sandbox2D::OnEvent(Angel3D::Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Sandbox
