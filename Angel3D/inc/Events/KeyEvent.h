#pragma once

#include "Events/Event.h"

namespace Angel3D
{
  namespace Events
  {
    class ANGEL3D_API KeyEvent : public Event
    {
      public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
      protected:
        KeyEvent(int f_keyCode)
        : m_KeyCode(f_keyCode)
        {}
        int m_KeyCode;
    };

    class ANGEL3D_API KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(int f_keyCode, int f_repeatCount)
        : KeyEvent(f_keyCode),
          m_RepeatCount(f_repeatCount)
        {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
          std::stringstream ss;
          ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " times)";
          return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
      private:
        int m_RepeatCount;
    };

    class ANGEL3D_API KeyReleasedEvent : public KeyEvent
    {
      public:
        KeyReleasedEvent(int f_keyCode)
        : KeyEvent(f_keyCode)
        {}

        std::string ToString() const override
        {
          std::stringstream ss;
          ss << "KeyReleasedEvent " << m_KeyCode;
          return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
  } // Events
} // Angel3d