#pragma once

#include "Renderer/Camera.h"
#include "Core/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Engine::Renderer
{
  class OrthographicCameraController
  {
    public:
      OrthographicCameraController(float f_aspectRatio, bool f_rotation = false);

      void OnUpdate(Engine::Core::Timestep f_timestep);
      void OnEvent(Engine::Events::Event& f_e);
      void OnResize(float f_width, float f_height);

      OrthographicCamera& GetCamera() { return m_Camera; }
      const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
      bool OnMouseScrolled(Engine::Events::MouseScrolledEvent& f_e);
      bool OnWindowResized(Engine::Events::WindowResizeEvent& f_e);

    private:
      float              m_AspectRatio;
      float              m_ZoomLevel = 1.0f;
      OrthographicCamera m_Camera;

      bool               m_Rotation;

      glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
      float     m_CameraRotation         = 0.0f;
      float     m_CameraTranslationSpeed = 1.0f;
      float     m_CameraRotationSpeed    = 1.0f;
  };
} // namespace Engine::Renderer
