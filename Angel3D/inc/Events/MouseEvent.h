#pragma once

#include "Events/Event.h"
#include "Core/Input.h"

namespace Angel3D::Events
{
  class MouseMovedEvent : public Event
  {
    public:
      MouseMovedEvent(float f_x, float f_y)
      : m_MouseX(f_x),
        m_MouseY(f_y)
      {}

      inline float GetX() const { return m_MouseX; }
      inline float GetY() const { return m_MouseY; }

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "MouseMovedEvent(" << m_MouseX << ", " << m_MouseY << ")";
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseMoved)
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
      float m_MouseX;
      float m_MouseY;
  };

  class MouseScrolledEvent : public Event
  {
    public:
      MouseScrolledEvent(float f_xOffset, float f_yOffset)
      : m_xOffset(f_xOffset),
        m_yOffset(f_yOffset)
      {}

      inline float GetXOffset() const { return m_xOffset; }
      inline float GetYOffset() const { return m_yOffset; }

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "MouseScrolledEvent(" << m_xOffset << ", " << m_yOffset << ")";
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseScrolled)
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
      float m_xOffset;
      float m_yOffset;
  };

  class MouseButtonEvent : public Event
  {
    public:
      inline Angel3D::Core::MouseCode GetMouseButton() const { return m_Button; }

      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
      MouseButtonEvent(Angel3D::Core::MouseCode f_button)
      : m_Button(f_button)
      {}

      Angel3D::Core::MouseCode m_Button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent
  {
    public:
      MouseButtonPressedEvent(Angel3D::Core::MouseCode f_button)
      : MouseButtonEvent(f_button)
      {}

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<int16_t>(m_Button);
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent
  {
    public:
      MouseButtonReleasedEvent(Angel3D::Core::MouseCode f_button)
      : MouseButtonEvent(f_button)
      {}

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<int16_t>(m_Button);
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseButtonReleased)
  };
} // namespace Angel3d
