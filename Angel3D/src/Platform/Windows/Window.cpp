#include "Core/BaseWindow.h"
#include "Platform/Windows/Window.h"
#include "Core/Log.h"

Angel3D::Core::BaseWindow* Angel3D::Core::BaseWindow::Create(const Angel3D::Core::WindowProps& f_props)
{
  return new Angel3D::Platform::Windows::Window(f_props);
}

namespace Angel3D
{
  namespace Platform
  {
    namespace Windows
    {
      static bool g_GLFWWindowInitialized = false;

      Window::Window(const Angel3D::Core::WindowProps& f_props)
      {
        Init(f_props);
      }

      Window::~Window()
      {
        Shutdown();
      }

      void Window::Init(const Angel3D::Core::WindowProps& f_props)
      {
        m_data.m_Title  = f_props.m_Title;
        m_data.m_Width  = f_props.m_Width;
        m_data.m_Height = f_props.m_Height;

        ANGEL3D_CORE_INFO("Creating Window {0} with ({1}, {2}) resolution.", f_props.m_Title, f_props.m_Width, f_props.m_Height);

        if(!g_GLFWWindowInitialized)
        {
          int success = glfwInit();
          ANGEL3D_CORE_ASSERT(success, "Could not initialize GLFW.")

          g_GLFWWindowInitialized = true;
        }

        m_window = glfwCreateWindow((int)m_data.m_Width, (int)m_data.m_Height,
                                    m_data.m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);
      }

      void Window::Shutdown()
      {
        glfwDestroyWindow(m_window);
      }

      void Window::OnUpdate()
      {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
      }

      void Window::SetVSync(bool f_enabled)
      {
        if(f_enabled)
        {
          glfwSwapInterval(1);
        }
        else
        {
          glfwSwapInterval(0);
        }

        m_data.m_vSync = f_enabled;
      }

      bool Window::IsVSync() const
      {
        return m_data.m_vSync;
      }
    } // namespace Windows
  } // namespace Platform
} // namespace Angel3D