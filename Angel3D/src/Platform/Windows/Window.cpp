#include "Core/BaseWindow.h"
#include "Platform/Windows/Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Core/Log.h"

#include "glad/glad.h"

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

      static void GLFWErrorCallbackFn(int error_code, const char* description)
      {
        ANGEL3D_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
      }

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
          glfwSetErrorCallback(GLFWErrorCallbackFn);
          g_GLFWWindowInitialized = true;
        }

        m_window = glfwCreateWindow((int)m_data.m_Width, (int)m_data.m_Height,
                                    m_data.m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ANGEL3D_CORE_ASSERT(status, "Failed to initialize GLAD");

        glfwSetWindowUserPointer(m_window, &m_data);
        SetVSync(true);

        // Set GLFW Callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
          data.m_Width = width;
          data.m_Height = height;

          Events::WindowResizeEvent event(width, height);
          data.m_eventCallbackFn(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
          Events::WindowCloseEvent event;
          data.m_eventCallbackFn(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

          switch (action)
          {
            case GLFW_PRESS:
            {
              Events::KeyPressedEvent event(key, 0);
              data.m_eventCallbackFn(event);
              break;
            }
            case GLFW_RELEASE:
            {
              Events::KeyReleasedEvent event(key);
              data.m_eventCallbackFn(event);
              break;
            }
            case GLFW_REPEAT:
            {
              Events::KeyPressedEvent event(key, 1);
              data.m_eventCallbackFn(event);
              break;
            }
            default:
              break;
          }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
          Events::KeyTypedEvent event(codepoint);
          data.m_eventCallbackFn(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

          switch (action)
          {
            case GLFW_PRESS:
            {
              Events::MouseButtonPressedEvent event(button);
              data.m_eventCallbackFn(event);
              break;
            }
            case GLFW_RELEASE:
            {
              Events::MouseButtonReleasedEvent event(button);
              data.m_eventCallbackFn(event);
              break;
            }
            default:
              break;
          }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

          Events::MouseScrolledEvent event((float)xoffset, (float)yoffset);
          data.m_eventCallbackFn(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
        {
          WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

          Events::MouseMovedEvent event((float)xpos, (float)ypos);
          data.m_eventCallbackFn(event);
        });
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