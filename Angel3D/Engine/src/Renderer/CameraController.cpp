#include "Renderer/CameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Engine::Renderer
{
  OrthographicCameraController::OrthographicCameraController(float f_aspectRatio, bool f_rotation)
  : m_AspectRatio(f_aspectRatio),
    m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
    m_Rotation(f_rotation)
  {

  }

  void OrthographicCameraController::OnUpdate(Engine::Core::Timestep f_timestep)
	{
    PROFILE_FUNCTION();

		if(Engine::Core::Input::IsKeyPressed(KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}
		else if(Engine::Core::Input::IsKeyPressed(KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}

		if(Engine::Core::Input::IsKeyPressed(KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}
		else if(Engine::Core::Input::IsKeyPressed(KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}

		if (m_Rotation)
		{
			if(Engine::Core::Input::IsKeyPressed(KEY_Q))
      {
				m_CameraRotation += m_CameraRotationSpeed * f_timestep;
      }
      else if(Engine::Core::Input::IsKeyPressed(KEY_E))
			{
        m_CameraRotation -= m_CameraRotationSpeed * f_timestep;
      }

			if (m_CameraRotation > 180.0f)
      {
				m_CameraRotation -= 360.0f;
      }
      else if (m_CameraRotation <= -180.0f)
			{
        m_CameraRotation += 360.0f;
      }

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

  void OrthographicCameraController::OnEvent(Engine::Events::Event &f_e)
  {
    PROFILE_FUNCTION();

    Engine::Events::EventDispatcher dispatcher(f_e);
    dispatcher.Dispatch<Engine::Events::MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<Engine::Events::WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
  }

  void OrthographicCameraController::OnResize(float width, float height)
  {
    m_AspectRatio = width / height;
    m_Camera.SetProjectioMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
  }

  bool OrthographicCameraController::OnMouseScrolled(
      Engine::Events::MouseScrolledEvent &f_e) {
    PROFILE_FUNCTION();

    m_ZoomLevel -= f_e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjectioMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
  }

  bool OrthographicCameraController::OnWindowResized(Engine::Events::WindowResizeEvent &f_e)
  {
    PROFILE_FUNCTION();

    OnResize((float)f_e.GetWidth(), (float)f_e.GetHeight());
    return false;
  }

} // namespace Engine::Renderer

