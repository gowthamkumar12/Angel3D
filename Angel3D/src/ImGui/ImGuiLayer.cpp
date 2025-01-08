#include "ImGui/ImGuiLayer.h"
#include "Core/Application.h"
#include "Core/KeyCodes.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

// TEMPORARY
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Angel3D::ImGuiImpl
{
  ImGuiLayer::ImGuiLayer()
  : Angel3D::Core::Layer("ImGuiLayer")
  {
  }

  void ImGuiLayer::OnAttach()
  {
    ANGEL3D_PROFILE_FUNCTION();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Angel3D::Core::Application& app = Angel3D::Core::Application::Get();
    GLFWwindow* window              = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
  }

  void ImGuiLayer::OnDetach()
  {
    ANGEL3D_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiLayer::OnEvent(Angel3D::Events::Event& f_e)
  {
    ImGuiIO& io = ImGui::GetIO();
		f_e.m_Handled |= f_e.IsInCategory(Angel3D::Events::EventCategory::EventCategoryMouse) & io.WantCaptureMouse;
		f_e.m_Handled |= f_e.IsInCategory(Angel3D::Events::EventCategory::EventCategoryKeyboard) & io.WantCaptureKeyboard;
  }

  void ImGuiLayer::Begin()
  {
    ANGEL3D_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void ImGuiLayer::End()
  {
    ANGEL3D_PROFILE_FUNCTION();

    ImGuiIO& io = ImGui::GetIO();
    Angel3D::Core::Application& app = Angel3D::Core::Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }
} // namespace Angel3D
