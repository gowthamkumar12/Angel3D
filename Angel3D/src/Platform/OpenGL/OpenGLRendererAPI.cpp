#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Angel3D::Platform::OpenGL
{
  void OpenGLRendererAPI::Init()
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void OpenGLRendererAPI::SetClearColor(const glm::vec4 &f_color)
  {
    glClearColor(f_color.r, f_color.g, f_color.b, f_color.b);
  }

  void OpenGLRendererAPI::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRendererAPI::DrawIndexed(const Angel3D::Core::Ref<Angel3D::Renderer::VertexArray> &f_vertexArray)
  {
    glDrawElements(GL_TRIANGLES, f_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
  }

} // namespace Angel3D::Platform::OpenGL
