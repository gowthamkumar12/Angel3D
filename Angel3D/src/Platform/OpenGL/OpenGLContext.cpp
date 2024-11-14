#include "Platform/OpenGL/OpenGLContext.h"
#include "Core/Log.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

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
  }

  void OpenGLContext::SwapBuffers()
  {
    glfwSwapBuffers(m_WindowHandle);
  }
} // namespace Angel3D::Platform::OpenGL


