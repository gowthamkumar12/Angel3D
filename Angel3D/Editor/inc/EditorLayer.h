#pragma once

#include "Engine.h"

namespace Engine
{
  class Editor : public Core::Layer
  {
    public:
      Editor();
      virtual ~Editor() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnUpdate(Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Events::Event& f_e) override;

    private:
      Renderer::OrthographicCameraController m_CameraController;

      // TODO
      Core::Ref<Renderer::VertexArray> m_vertexArray;
      Core::Ref<Renderer::Shader>      m_Shader;
      Core::Ref<Renderer::Framebuffer> m_Framebuffer;

      Core::Ref<Engine::Scene::Scene>  m_ActiveScene;
		  Engine::Scene::Entity            m_SquareEntity;

      Engine::Scene::Entity            m_CameraEntity;
      Engine::Scene::Entity            m_CameraEntity_2;
      bool                             m_PrimaryCamera = true;

      Core::Ref<Renderer::Texture2D>   m_Texture;
      glm::vec2                        m_ViewportSize{ 0.0f, 0.0f };
      glm::vec4                        m_tileSquareColor{ 1.0f, 1.0f, 1.0f, 1.0f };

      bool m_ViewportFocused = false;
      bool m_ViewportHovered = false;
  };
} // namespace Engine
