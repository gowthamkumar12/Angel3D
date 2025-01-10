#pragma once

#include "Renderer/RenderCommand.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"

namespace Engine::Renderer
{
  class Renderer
  {
    public:
      static void Init();
      static void Shutdown();

      static void OnWindowResize(uint32_t f_width, uint32_t f_height);

      static void BeginScene(Engine::Renderer::OrthographicCamera& f_camera);
      static void EndScene();

      static void Submit(const Engine::Core::Ref<Shader>&      f_Shader,
                         const Engine::Core::Ref<VertexArray>& f_vertexArray,
                         const glm::mat4&                    f_transform = glm::mat4(1.0f));

      inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
      struct SceneData
      {
        glm::mat4 m_ViewProjectionMatrix;
      };

      static Engine::Core::Scope<SceneData> s_SceneData;
  };
} // namespace Engine::Renderer
