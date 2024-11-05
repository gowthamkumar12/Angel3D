#pragma once

#include "Events/Event.h"

namespace Angel3D::Events
{
  class ANGEL3D_API WindowResizeEvent : public Event
  {
    public:
      WindowResizeEvent(unsigned int f_width, unsigned int f_height)
      : m_width(f_width),
        m_height(f_height)
      {}

      inline unsigned int GetWidth() const { return m_width; }
      inline unsigned int GetHeight() const { return m_height; }

      std::string ToString() const override
      {
        std::stringstream ss;
        ss << "WindowResizeEvent(" << m_width << ", " << m_height <<")";
        return ss.str();
      }

      EVENT_CLASS_TYPE(WindowResize)
      EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
      unsigned int m_width;
      unsigned int m_height;
  };

  class ANGEL3D_API WindowCloseEvent : public Event
  {
    public:
      WindowCloseEvent()
      {}

      EVENT_CLASS_TYPE(WindowClose)
      EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };

  class ANGEL3D_API AppTickEvent : public Event
  {
    public:
      AppTickEvent()
      {}

      EVENT_CLASS_TYPE(AppTick)
      EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };

  class ANGEL3D_API AppUpdateEvent : public Event
  {
    public:
      AppUpdateEvent()
      {}

      EVENT_CLASS_TYPE(AppUpdate)
      EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };

  class ANGEL3D_API AppRenderEvent : public Event
  {
    public:
      AppRenderEvent()
      {}

      EVENT_CLASS_TYPE(AppRender)
      EVENT_CLASS_CATEGORY(EventCategoryApplication)
  };
} // Angel3d