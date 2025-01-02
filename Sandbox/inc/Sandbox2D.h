#pragma once

#include "Angel3D.h"

namespace Sandbox
{
  class Sandbox2D : public Angel3D::Core::Layer
  {
    public:
      Sandbox2D();
      virtual ~Sandbox2D() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnUpdate(Angel3D::Core::Timestep f_ts) override;
      virtual void OnImGuiRender() override;
      virtual void OnEvent(Angel3D::Events::Event& f_e) override;

    private:
      Angel3D::Renderer::OrthographicCameraController m_CameraController;

      // TODO
      Angel3D::Core::Ref<Angel3D::Renderer::VertexArray> m_vertexArray;
      Angel3D::Core::Ref<Angel3D::Renderer::Shader>      m_Shader;
      Angel3D::Core::Ref<Angel3D::Renderer::Texture2D>   m_Texture;
      glm::vec4                                          m_tileSquareColor{1.0f, 1.0f, 1.0f, 1.0f};

      struct ProfileResult
      {
        const char* f_Name;
        float       f_Time;
      };

      std::vector<ProfileResult> m_ProfileResults;
  };
} // namespace Sandbox
