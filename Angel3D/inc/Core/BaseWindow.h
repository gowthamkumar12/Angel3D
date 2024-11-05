#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Angel3D
{
  namespace Core
  {
    struct WindowProps
    {
      std::string  m_Title;
      unsigned int m_Width;
      unsigned int m_Height;

      WindowProps(const std::string& f_title = "Angel3D Engine",
                  unsigned int       f_width = 1920U,
                  unsigned int       f_height= 1080U)
      : m_Title(f_title),
        m_Width(f_width),
        m_Height(f_height)
      {}
    };

    // Interface representing a desktop system based window
    class ANGEL3D_API BaseWindow
    {
      public:
        using EventCallbackfn = std::function<void(Angel3D::Events::Event&)>;

        virtual ~BaseWindow() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackfn& f_callback) = 0;
        virtual void SetVSync(bool f_enabled) = 0;
        virtual bool IsVSync() const = 0;

        static BaseWindow* Create(const WindowProps& f_props = WindowProps());
    };
  } // namespace Core
} // namespace Angel3D
