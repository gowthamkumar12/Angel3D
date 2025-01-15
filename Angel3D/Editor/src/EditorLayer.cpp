#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
  Editor::Editor()
  : Core::Layer("Engine Editor"),
	  m_CameraController(1280.0f / 720.0f)
  {}

  void Editor::OnAttach()
  {
    PROFILE_FUNCTION();

    m_Texture = Renderer::Texture2D::Create("Assets/textures/Checkerboard.png");

    Renderer::FramebufferSpecification frameBufferSpecs;
    frameBufferSpecs.Width = 1280;
    frameBufferSpecs.Height = 720;
    m_Framebuffer = Renderer::Framebuffer::Create(frameBufferSpecs);

    m_ActiveScene = Core::CreateRef<Engine::Scene::Scene>();

    // Entity
		auto square = m_ActiveScene->CreateEntity("Square");
		square.AddComponent<Engine::Scene::SpriteRendererComponent>(glm::vec4{1.0f, 0.5647f, 0.6941f, 1.0f});

		m_SquareEntity = square;
  }

  void Editor::OnDetach()
  {
    PROFILE_FUNCTION();
  }

  void Editor::OnUpdate(Core::Timestep f_ts)
  {
    PROFILE_FUNCTION();

    // Resize
    Engine::Renderer::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		if (m_ViewportSize.x > 0.0f &&
        m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			  (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

    // Update
    if(m_ViewportFocused)
    {
      m_CameraController.OnUpdate(f_ts);
    }

    Renderer::Renderer2D::ResetStats();
    m_Framebuffer->Bind();
    Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
    Renderer::RenderCommand::Clear();

    // Scene-1 Start
    Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());

    // Update scene
		m_ActiveScene->OnUpdate(f_ts);

    Renderer::Renderer2D::EndScene();
    // Scene-1 End

    m_Framebuffer->Unbind();
  }

  void Editor::OnImGuiRender()
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
        if (ImGui::MenuItem("Exit")) Core::Application::Get().Close();
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    // Statistics Window
    ImGui::Begin("Statistics");

      auto stats = Renderer::Renderer2D::GetStats();
      ImGui::Text("Renderer2D Statistics");
      ImGui::Text("Draw Calls : %d", stats.DrawCalls);
      ImGui::Text("Quads      : %d", stats.QuadCount);
      ImGui::Text("Vertices   : %d", stats.GetTotalVertexCount());
      ImGui::Text("Indices    : %d", stats.GetTotalIndexCount());

      if(m_SquareEntity)
      {
        ImGui::Separator();
        ImGui::Text("%s", m_SquareEntity.GetComponent<Engine::Scene::TagComponent>().Tag.c_str());

        auto& squareColor = m_SquareEntity.GetComponent<Engine::Scene::SpriteRendererComponent>().Color;
		    ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));

        ImGui::Separator();
      }

    ImGui::End();

    // Viewport window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport");

      m_ViewportFocused = ImGui::IsWindowFocused();
      m_ViewportHovered = ImGui::IsWindowHovered();
      Core::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

      ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
      m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
      uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
      ImGui::Image((unsigned long long)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
    ImGui::PopStyleVar();


    ImGui::End();
  }

  void Editor::OnEvent(Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Engine
