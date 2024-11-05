#pragma once

#include "Core/Layer.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

namespace Angel3D::ImGuiImpl
{
  class ANGEL3D_API ImGuiLayer : public Angel3D::Core::Layer
  {
    public:
      ImGuiLayer();
      ~ImGuiLayer();

      void OnAttach() override;
      void OnDetach() override;
      void OnUpdate() override;
      void OnEvent(Angel3D::Events::Event& f_e) override;

    private:
      // Mouse event handlers
      bool OnMouseButtonPressedEvent(Angel3D::Events::MouseButtonPressedEvent& f_e);
      bool OnMouseButtonReleasedEvent(Angel3D::Events::MouseButtonReleasedEvent& f_e);
      bool OnMouseScrolledEvent(Angel3D::Events::MouseScrolledEvent& f_e);
      bool OnMouseMovedEvent(Angel3D::Events::MouseMovedEvent& f_e);

      // Key event handlers
      bool OnKeyPressedEvent(Angel3D::Events::KeyPressedEvent& f_e);
      bool OnKeyReleasedEvent(Angel3D::Events::KeyReleasedEvent& f_e);
      bool OnKeyTypedEvent(Angel3D::Events::KeyTypedEvent& f_e);

      // Window event handlers
      bool OnWindowResizeEvent(Angel3D::Events::WindowResizeEvent& f_e);

    private:
      float m_Time = 0.0f;
  };
} // namespace Angel3D
