#include "Renderer/CameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Angel3D::Renderer
{
  OrthographicCameraController::OrthographicCameraController(float f_aspectRatio, bool f_rotation)
  : m_AspectRatio(f_aspectRatio),
    m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
    m_Rotation(f_rotation)
  {

  }

  void OrthographicCameraController::OnUpdate(Angel3D::Core::Timestep f_timestep)
	{
		if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}
		else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}

		if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}
		else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * f_timestep;
		}

		if (m_Rotation)
		{
			if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_Q))
      {
				m_CameraRotation += m_CameraRotationSpeed * f_timestep;
      }
      else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_E))
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

  void OrthographicCameraController::OnEvent(Angel3D::Events::Event &f_e)
  {
    Angel3D::Events::EventDispatcher dispatcher(f_e);
    dispatcher.Dispatch<Angel3D::Events::MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<Angel3D::Events::WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
  }

  bool OrthographicCameraController::OnMouseScrolled(Angel3D::Events::MouseScrolledEvent &f_e)
  {
    m_ZoomLevel -= f_e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjectioMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
  }

  bool OrthographicCameraController::OnWindowResized(Angel3D::Events::WindowResizeEvent &f_e)
  {
    m_AspectRatio = (float)f_e.GetWidth() / (float)f_e.GetHeight();
    m_Camera.SetProjectioMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
  }

} // namespace Angel3D::Renderer

