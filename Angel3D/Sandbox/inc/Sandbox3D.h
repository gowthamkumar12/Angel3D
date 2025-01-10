#pragma once

#include "Engine.h"

namespace Sandbox
{
  class Sandbox3D : public Engine::Core::Layer
  {
    public:
      Sandbox3D();

      virtual void OnUpdate(Engine::Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Engine::Events::Event& f_e) override;

    private:
      Engine::Renderer::ShaderLibrary                    m_ShaderLibrary;
      Engine::Core::Ref<Engine::Renderer::VertexArray>  m_vertexArray;
      Engine::Core::Ref<Engine::Renderer::VertexArray>  m_squareVertexArray;
      Engine::Core::Ref<Engine::Renderer::Texture2D>    m_Texture, m_Logo;

      Engine::Renderer::OrthographicCameraController m_CameraController;

      glm::vec4 m_tileSquareColor{1.0f, 1.0f, 1.0f, 1.0f};
  };
} // namespace Sandbox
