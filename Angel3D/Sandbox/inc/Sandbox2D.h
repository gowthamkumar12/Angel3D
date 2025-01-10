#pragma once

#include "Engine.h"

namespace Sandbox
{
  class Sandbox2D : public Engine::Core::Layer
  {
    public:
      Sandbox2D();
      virtual ~Sandbox2D() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnUpdate(Engine::Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Engine::Events::Event& f_e) override;

    private:
      Engine::Renderer::OrthographicCameraController m_CameraController;

      // TODO
      Engine::Core::Ref<Engine::Renderer::VertexArray> m_vertexArray;
      Engine::Core::Ref<Engine::Renderer::Shader>      m_Shader;
      Engine::Core::Ref<Engine::Renderer::Texture2D>   m_Texture;
      glm::vec4                                          m_tileSquareColor{1.0f, 1.0f, 1.0f, 1.0f};
  };
} // namespace Sandbox
