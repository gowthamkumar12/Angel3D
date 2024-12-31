#pragma once

#include "Angel3D.h"

namespace Sandbox
{
  class Sandbox3D : public Angel3D::Core::Layer
  {
    public:
      Sandbox3D();

      virtual void OnUpdate(Angel3D::Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Angel3D::Events::Event& f_e) override;

    private:
      Angel3D::Renderer::ShaderLibrary                    m_ShaderLibrary;
      Angel3D::Core::Ref<Angel3D::Renderer::VertexArray>  m_vertexArray;
      Angel3D::Core::Ref<Angel3D::Renderer::VertexArray>  m_squareVertexArray;
      Angel3D::Core::Ref<Angel3D::Renderer::Texture2D>    m_Texture, m_Logo;

      Angel3D::Renderer::OrthographicCameraController m_CameraController;

      glm::vec4 m_tileSquareColor{1.0f, 1.0f, 1.0f, 1.0f};
  };
} // namespace Sandbox
