#include "ImGui/ImGuiLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Core/Application.h"

// TEMPORARY
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Angel3D
{
  namespace ImGuiImpl
  {
    ImGuiLayer::ImGuiLayer()
    : Angel3D::Core::Layer("ImGuiLayer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {

    }

    void ImGuiLayer::OnAttach()
    {
      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGuiIO& io = ImGui::GetIO();
      io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
      io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

      // TEMPORARY: should eventually use our key codes
      io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
      io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
      io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
      io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
      io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
      io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
      io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
      io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
      io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
      io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
      io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
      io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
      io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
      io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
      io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
      io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
      io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
      io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
      io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
      io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
      io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

      ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
      ImGuiIO& io = ImGui::GetIO();
      Angel3D::Core::Application& app = Angel3D::Core::Application::Get();
      io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

      float time = (float)glfwGetTime();
      io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
      m_Time = time;

      ImGui_ImplOpenGL3_NewFrame();
      ImGui::NewFrame();

      static bool show = true;
      ImGui::ShowDemoWindow(&show);

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Angel3D::Events::Event& f_e)
    {
      Angel3D::Events::EventDispatcher dispatcher(f_e);

      // Mouse event binding
      dispatcher.Dispatch<Angel3D::Events::MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<Angel3D::Events::MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<Angel3D::Events::MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
      dispatcher.Dispatch<Angel3D::Events::MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));

      // Key event binging
      dispatcher.Dispatch<Angel3D::Events::KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
      dispatcher.Dispatch<Angel3D::Events::KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
      dispatcher.Dispatch<Angel3D::Events::KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

      // Window event binding
      dispatcher.Dispatch<Angel3D::Events::WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(Angel3D::Events::MouseButtonPressedEvent &f_e)
    {
      ImGuiIO & io = ImGui::GetIO();
      io.MouseDown[f_e.GetMouseButton()] = true;

      return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(Angel3D::Events::MouseButtonReleasedEvent &f_e)
    {
      ImGuiIO & io = ImGui::GetIO();
      io.MouseDown[f_e.GetMouseButton()] = false;

      return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(Angel3D::Events::MouseScrolledEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseWheelH += f_e.GetXOffset();
      io.MouseWheel  += f_e.GetYOffset();

      return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(Angel3D::Events::MouseMovedEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.MousePos = ImVec2(f_e.GetX(), f_e.GetY());

      return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(Angel3D::Events::KeyPressedEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[f_e.GetKeyCode()] = true;

      io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
      io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
      io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
      io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

      return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(Angel3D::Events::KeyReleasedEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[f_e.GetKeyCode()] = false;

      return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(Angel3D::Events::KeyTypedEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      int keycode = f_e.GetKeyCode();
      if(keycode > 0 && keycode < 0x10000)
      {
        io.AddInputCharacter((unsigned int)keycode);
      }

      return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(Angel3D::Events::WindowResizeEvent &f_e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.DisplaySize = ImVec2(f_e.GetWidth(), f_e.GetHeight());
      io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
      glViewport(0, 0, f_e.GetWidth(), f_e.GetHeight());

      return false;
    }
  } // namespace ImGuiImpl
} // namespace Angel3D
