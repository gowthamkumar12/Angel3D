#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Angel3D::Renderer
{
  Angel3D::Core::Scope<Renderer::SceneData> Renderer::s_SceneData = Angel3D::Core::CreateScope<Renderer::SceneData>();

  void Renderer::Init()
  {
    RenderCommand::Init();
    Renderer2D::Init();
  }
  void Renderer::OnWindowResize(uint32_t f_width, uint32_t f_height)
  {
    RenderCommand::SetViewport(0, 0, f_width, f_height);
  }

  void Renderer::BeginScene(Angel3D::Renderer::OrthographicCamera& f_camera)
  {
    s_SceneData->m_ViewProjectionMatrix = f_camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const Angel3D::Core::Ref<Shader>&      f_Shader,
                        const Angel3D::Core::Ref<VertexArray>& f_vertexArray,
                        const glm::mat4&                       f_transform)
  {
    f_Shader->Bind();
    std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(f_Shader)
                                    ->UploadUniformMat4("u_ViewProjectionMatrix", s_SceneData->m_ViewProjectionMatrix);
    std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(f_Shader)
                                    ->UploadUniformMat4("u_Transform", f_transform);

    f_vertexArray->Bind();
    RenderCommand::DrawIndexed(f_vertexArray);
  }
} // namespace Angel3D::Renderer
