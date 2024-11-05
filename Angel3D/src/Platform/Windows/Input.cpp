#include "Platform/Windows/Input.h"
#include "GLFW/glfw3.h"
#include "Core/Application.h"

Angel3D::Core::Input* Angel3D::Core::Input::s_Instance = new Angel3D::Platform::Windows::WindowsInput();

namespace Angel3D::Platform::Windows
{
  bool WindowsInput::IsKeyPressedImpl(int f_keycode)
  {
    auto window = static_cast<GLFWwindow*>(Angel3D::Core::Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetKey(window, f_keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool WindowsInput::IsMouseButtonPressedImpl(int f_button)
  {
    auto window = static_cast<GLFWwindow*>(Angel3D::Core::Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetMouseButton(window, f_button);
    return state = GLFW_PRESS;
  }

  std::pair<float, float> WindowsInput::GetMousePositionImpl()
  {
    auto window = static_cast<GLFWwindow*>(Angel3D::Core::Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float)xpos, (float)ypos};
  }

  float WindowsInput::GetMouseXImpl()
  {
    auto [x, y] = GetMousePositionImpl();
    return x;
  }

  float WindowsInput::GetMouseYImpl()
  {
    auto [x, y] = GetMousePositionImpl();
    return y;
  }
} // namespace Angel3D::Platform::Windows
