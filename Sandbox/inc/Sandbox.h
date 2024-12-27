#pragma once

#include "Angel3D.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox
{
  class MainApplicationLayer : public Angel3D::Core::Layer
  {
    public:
      MainApplicationLayer();

      virtual void OnUpdate(Angel3D::Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Angel3D::Events::Event& f_e) override;

    private:
      Angel3D::Core::Ref<Angel3D::Renderer::VertexArray>  m_vertexArray;
      Angel3D::Core::Ref<Angel3D::Renderer::VertexArray>  m_squareVertexArray;
      Angel3D::Core::Ref<Angel3D::Renderer::Shader>       m_Shader;
      Angel3D::Core::Ref<Angel3D::Renderer::Shader>       m_TileShader, m_TextureShader;
      Angel3D::Core::Ref<Angel3D::Renderer::Texture2D>    m_Texture, m_Logo;

    private:
      Angel3D::Renderer::OrthographicCamera m_Camera;
      glm::vec3                             m_CameraPosition;
      float                                 m_CameraMoveSpeed     = 5.0f;
      float                                 m_CameraRotation      = 0.0f;
      float                                 m_CameraRotationSpeed = 90.0f;

      glm::vec3 m_tileSquareColor{1.0f, 1.0f, 1.0f};
  };
} // namespace Sandbox
