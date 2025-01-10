#include "Platform/OpenGL/OpenGLContext.h"
#include "Core/Log.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <GL/GL.h>

namespace Engine::Platform::OpenGL
{
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
  : m_WindowHandle(windowHandle)
  {
    CORE_ASSERT(windowHandle, "Window handle is null!");
  }

  void OpenGLContext::Init()
  {
    PROFILE_FUNCTION();

    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CORE_ASSERT(status, "Failed to initialize GLAD");

    CORE_INFO("OpenGL Info:");
    CORE_INFO("  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    CORE_INFO("  Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    #ifdef ENABLE_ASSERTS
      int versionMajor;
      int versionMinor;
      glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
      glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
      CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Engine requires at least OpenGL version 4.5!");
    #endif
  }

  void OpenGLContext::SwapBuffers()
  {
    PROFILE_FUNCTION();

    glfwSwapBuffers(m_WindowHandle);
  }
} // namespace Engine::Platform::OpenGL


