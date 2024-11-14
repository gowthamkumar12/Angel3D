#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Angel3D::Platform::OpenGL
{
  class OpenGLContext : public Angel3D::Renderer::GraphicsContext
  {
    public:
      OpenGLContext(GLFWwindow* windowHandle);
      virtual void Init() override;
      virtual void SwapBuffers() override;

    private:
      GLFWwindow* m_WindowHandle;
  };
} // namespace Angel3D::Platform::OpenGL
