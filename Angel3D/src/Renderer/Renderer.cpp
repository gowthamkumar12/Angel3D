#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Angel3D::Renderer
{
  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

  void Renderer::BeginScene(Angel3D::Renderer::OrthographicCamera& f_camera)
  {
    m_SceneData->m_ViewProjectionMatrix = f_camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const std::shared_ptr<Shader>&      f_Shader,
                        const std::shared_ptr<VertexArray>& f_vertexArray,
                        const glm::mat4&                    f_transform)
  {
    f_Shader->Bind();
    std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(f_Shader)
                                    ->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->m_ViewProjectionMatrix);
    std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(f_Shader)
                                    ->UploadUniformMat4("u_Transform", f_transform);

    f_vertexArray->Bind();
    RenderCommand::DrawIndexed(f_vertexArray);
  }
} // namespace Angel3D::Renderer
