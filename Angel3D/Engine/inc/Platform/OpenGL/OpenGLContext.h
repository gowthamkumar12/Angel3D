#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Engine::Platform::OpenGL
{
  class OpenGLContext : public Engine::Renderer::GraphicsContext
  {
    public:
      OpenGLContext(GLFWwindow* windowHandle);
      virtual void Init() override;
      virtual void SwapBuffers() override;

    private:
      GLFWwindow* m_WindowHandle;
  };
} // namespace Engine::Platform::OpenGL
