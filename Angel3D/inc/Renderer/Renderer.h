#pragma once

#include "Renderer/RenderCommand.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"

namespace Angel3D::Renderer
{
  class Renderer
  {
    public:
      static void BeginScene(Angel3D::Renderer::OrthographicCamera& f_camera);
      static void EndScene();

      static void Submit(const std::shared_ptr<Shader>&      f_Shader,
                         const std::shared_ptr<VertexArray>& f_vertexArray,
                         const glm::mat4&                    f_transform = glm::mat4(1.0f));

      inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
      struct SceneData
      {
        glm::mat4 m_ViewProjectionMatrix;
      };

      static SceneData* m_SceneData;
  };
} // namespace Angel3D::Renderer
