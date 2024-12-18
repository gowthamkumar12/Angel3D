#pragma once

#include "Core/Core.h"

namespace Angel3D::Events
{
  // This enum defines what are the types of event that exists for this project.
  enum class EventType
  {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
  };

  // This enum defines what category the event falls under.
  enum EventCategory
  {
    None = 0,
    EventCategoryApplication  = BIT(0),
    EventCategoryInput        = BIT(1),
    EventCategoryKeyboard     = BIT(2),
    EventCategoryMouse        = BIT(3),
    EventCategoryMouseButton  = BIT(4)
  };

  #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                  virtual EventType GetEventType() const override { return GetStaticType(); }\
                                  virtual const char* GetName() const override { return #type; }

  #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

  // Base class for the event.
  class ANGEL3D_API Event
  {
    public:
      virtual EventType GetEventType() const = 0;
      virtual const char* GetName() const = 0;
      virtual int GetCategoryFlags() const = 0;
      virtual std::string ToString() const { return GetName(); }

      inline bool IsInCategory(EventCategory f_category)
      {
        return GetCategoryFlags() & f_category;
      }

      virtual ~Event() = default;

      bool m_Handled = false;

    private:
      friend class EventDispatcher;
  };

  class EventDispatcher
  {
      template<typename T>
      using EventFn = std::function<bool(T&)>;
    public:
      EventDispatcher(Event& f_event)
      : m_Event(f_event)
      {}

      template<typename T>
      bool Dispatch(EventFn<T> func)
      {
        if(m_Event.GetEventType() == T::GetStaticType())
        {
          m_Event.m_Handled = func(*(T*)&m_Event);
          return true;
        }
        return false;
      }

    private:
      Event& m_Event;
  };

  inline std::ostream& operator<<(std::ostream& os, const Event& e)
  {
    return os << e.ToString();
  }
} // namespace Angel3D
