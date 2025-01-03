#pragma once

#include "Events/Event.h"
#include "Core/Input.h"

namespace Angel3D::Events
{
  class KeyEvent : public Event
  {
    public:
      inline Angel3D::Core::KeyCode GetKeyCode() const { return m_KeyCode; }

      EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
      KeyEvent(Angel3D::Core::KeyCode f_keyCode)
      : m_KeyCode(f_keyCode)
      {}
      Angel3D::Core::KeyCode m_KeyCode;
  };

  class KeyPressedEvent : public KeyEvent
  {
    public:
      KeyPressedEvent(Angel3D::Core::KeyCode f_keyCode, int f_repeatCount)
      : KeyEvent(f_keyCode),
        m_RepeatCount(f_repeatCount)
      {}

      inline int GetRepeatCount() const { return m_RepeatCount; }

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<int16_t>(m_KeyCode) << "(" << m_RepeatCount << " times)";
        return ss.str();
      }

      EVENT_CLASS_TYPE(KeyPressed)
    private:
      int m_RepeatCount;
  };

  class KeyReleasedEvent : public KeyEvent
  {
    public:
      KeyReleasedEvent(Angel3D::Core::KeyCode f_keyCode)
      : KeyEvent(f_keyCode)
      {}

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "KeyReleasedEvent " << static_cast<int16_t>(m_KeyCode);
        return ss.str();
      }

      EVENT_CLASS_TYPE(KeyReleased)
  };

  class KeyTypedEvent : public KeyEvent
  {
    public:
      KeyTypedEvent(Angel3D::Core::KeyCode f_keyCode)
      : KeyEvent(f_keyCode)
      {}

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << static_cast<int16_t>(m_KeyCode) ;
        return ss.str();
      }

      EVENT_CLASS_TYPE(KeyTyped)
  };
} // Angel3d