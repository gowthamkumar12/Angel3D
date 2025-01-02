#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

namespace Sandbox
{
  template<typename Fn>
  class Timer
  {
    public:
      Timer(const char* name, Fn&& func)
        : m_Name(name), m_Func(func), m_Stopped(false)
      {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
      }

      ~Timer()
      {
        if (!m_Stopped)
          Stop();
      }

      void Stop()
      {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        m_Stopped = true;
        float duration = (end - start) * 0.001f;
        m_Func({ m_Name, duration });
      }

    private:
      const char*                                        m_Name;
      Fn                                                 m_Func;
      std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
      bool                                               m_Stopped;
  };

  #define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

  Sandbox2D::Sandbox2D()
  : Angel3D::Core::Layer("Sandbox3D"),
	  m_CameraController(1920.0f / 1080.0f)
  {}

  void Sandbox2D::OnAttach()
  {
    m_Texture = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");
  }

  void Sandbox2D::OnDetach()
  {
  }

  void Sandbox2D::OnUpdate(Angel3D::Core::Timestep f_ts)
  {
    PROFILE_SCOPE("Sandbox2D::OnUpdate");

    // Update
		m_CameraController.OnUpdate(f_ts);

		// Render
		Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
		Angel3D::Renderer::RenderCommand::Clear();

		Angel3D::Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Angel3D::Renderer::Renderer2D::DrawQuad({-0.5f, -0.25f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
		Angel3D::Renderer::Renderer2D::DrawQuad({0.5f, -0.25f}, {0.5f, 0.5f}, {0.2f, 0.3f, 0.8f, 1.0f});
		Angel3D::Renderer::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_Texture);
		Angel3D::Renderer::Renderer2D::EndScene();

    // m_Shader->Bind();
		// // TODO Shader::SetMat4, Shader::SetFloat4
    // m_Shader->SetFloat4("u_Color", m_tileSquareColor);
    // Angel3D::Renderer::Renderer::Submit(m_Shader, m_vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
  }

  void Sandbox2D::OnImGuiRender()
  {
    ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_tileSquareColor));

    for (auto& result : m_ProfileResults)
    {
      char label[50];
      strcpy(label, "%.3fms ");
      strcat(label, result.f_Name);
      ImGui::Text(label, result.f_Time);
    }
    m_ProfileResults.clear();

		ImGui::End();
  }

  void Sandbox2D::OnEvent(Angel3D::Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Sandbox
