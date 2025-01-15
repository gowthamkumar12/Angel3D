#include "Core/BaseWindow.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/Windows/Window.h"
#include "Renderer/Renderer.h"

namespace Engine::Platform::Windows
{
  static uint8_t s_GLFWWindowInitialized = 0U;

  static void GLFWErrorCallbackFn(int error_code, const char* description)
  {
    CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
  }

  Window::Window(const Engine::Core::WindowProps& f_props)
  {
    PROFILE_FUNCTION();

    Init(f_props);
  }

  Window::~Window()
  {
    PROFILE_FUNCTION();

    Shutdown();
  }

  void Window::Init(const Engine::Core::WindowProps& f_props)
  {
    PROFILE_FUNCTION();

    m_data.m_Title  = f_props.m_Title;
    m_data.m_Width  = f_props.m_Width;
    m_data.m_Height = f_props.m_Height;

    CORE_INFO("Creating Window {0} with ({1}, {2}) resolution.", f_props.m_Title, f_props.m_Width, f_props.m_Height);

    if(s_GLFWWindowInitialized == 0)
    {
      PROFILE_SCOPE("Window::GLFW");

      CORE_INFO("Initializing GLFW");
      int success = glfwInit();
      CORE_ASSERT(success, "Could not initialize GLFW.")
      glfwSetErrorCallback(GLFWErrorCallbackFn);
      s_GLFWWindowInitialized = true;
    }

    {
      PROFILE_SCOPE("Window::GLFWCreateWindow");

      #if defined(DEBUG)
        if (Engine::Renderer::Renderer::GetAPI() == Engine::Renderer::RendererAPI::API::OPENGL)
        {
          glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        }
      #endif

      m_window = glfwCreateWindow((int)m_data.m_Width, (int)m_data.m_Height,
                                  m_data.m_Title.c_str(), nullptr, nullptr);
      ++s_GLFWWindowInitialized;
    }

    m_Context = Engine::Renderer::GraphicsContext::Create(m_window);
    m_Context->Init();

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
          Events::KeyPressedEvent event(static_cast<Engine::Core::KeyCode>(key), 0);
          data.m_eventCallbackFn(event);
          break;
        }
        case GLFW_RELEASE:
        {
          Events::KeyReleasedEvent event(static_cast<Engine::Core::KeyCode>(key));
          data.m_eventCallbackFn(event);
          break;
        }
        case GLFW_REPEAT:
        {
          Events::KeyPressedEvent event(static_cast<Engine::Core::KeyCode>(key), 1);
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
      Events::KeyTypedEvent event(static_cast<Engine::Core::KeyCode>(codepoint));
      data.m_eventCallbackFn(event);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch (action)
      {
        case GLFW_PRESS:
        {
          Events::MouseButtonPressedEvent event(static_cast<Engine::Core::MouseCode>(button));
          data.m_eventCallbackFn(event);
          break;
        }
        case GLFW_RELEASE:
        {
          Events::MouseButtonReleasedEvent event(static_cast<Engine::Core::MouseCode>(button));
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
    PROFILE_FUNCTION();

    glfwDestroyWindow(m_window);
    --s_GLFWWindowInitialized;

    if(s_GLFWWindowInitialized == 0)
    {
      CORE_INFO("Terminating GLFW window");
      glfwTerminate();
    }
  }

  void Window::OnUpdate()
  {
    PROFILE_FUNCTION();

    glfwPollEvents();
    m_Context->SwapBuffers();
  }

  void Window::SetVSync(bool f_enabled)
  {
    PROFILE_FUNCTION();

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
} // namespace Engine