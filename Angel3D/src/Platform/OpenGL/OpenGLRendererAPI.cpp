#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Angel3D::Platform::OpenGL
{
  void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id,
                             unsigned severity, int length, const char* message,	const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         ANGEL3D_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       ANGEL3D_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          ANGEL3D_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: ANGEL3D_CORE_TRACE(message); return;
		}

		ANGEL3D_CORE_ASSERT(false, "Unknown severity level!");
	}

  void OpenGLRendererAPI::Init()
  {
    ANGEL3D_PROFILE_FUNCTION();

    #ifdef ANGEL3D_DEBUG
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(OpenGLMessageCallback, nullptr);

      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    #endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
  }

  void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t f_width, uint32_t f_height)
  {
    glViewport(x, y, f_width, f_height);
  }

  void OpenGLRendererAPI::SetClearColor(const glm::vec4 &f_color)
  {
    glClearColor(f_color.r, f_color.g, f_color.b, f_color.b);
  }

  void OpenGLRendererAPI::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRendererAPI::DrawIndexed(const Angel3D::Core::Ref<Angel3D::Renderer::VertexArray> &f_vertexArray, uint32_t f_count)
  {
    uint32_t count = f_count ? f_count : f_vertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

} // namespace Angel3D::Platform::OpenGL
