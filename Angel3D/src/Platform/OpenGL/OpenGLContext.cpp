#include "Platform/OpenGL/OpenGLContext.h"
#include "Core/Log.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <GL/GL.h>

namespace Angel3D::Platform::OpenGL
{
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
  : m_WindowHandle(windowHandle)
  {
    ANGEL3D_CORE_ASSERT(windowHandle, "Window handle is null!");
  }

  void OpenGLContext::Init()
  {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ANGEL3D_CORE_ASSERT(status, "Failed to initialize GLAD");

    ANGEL3D_CORE_INFO("OpenGL Info:");
    ANGEL3D_CORE_INFO("  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    ANGEL3D_CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    ANGEL3D_CORE_INFO("  Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    #ifdef ANGEL3D_ENABLE_ASSERTS
      int versionMajor;
      int versionMinor;
      glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
      glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
      ANGEL3D_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Angel3D requires at least OpenGL version 4.5!");
    #endif
  }

  void OpenGLContext::SwapBuffers()
  {
    glfwSwapBuffers(m_WindowHandle);
  }
} // namespace Angel3D::Platform::OpenGL


