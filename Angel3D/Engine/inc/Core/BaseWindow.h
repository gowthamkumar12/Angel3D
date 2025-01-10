#pragma once

#include "Core/Core.h"
#include "Events/Event.h"

namespace Engine::Core
{
  struct WindowProps
  {
    std::string  m_Title;
    uint32_t     m_Width;
    uint32_t     m_Height;

    WindowProps(const std::string& f_title = "Engine Engine",
                uint32_t           f_width = 1280U,
                uint32_t           f_height= 720U)
    : m_Title(f_title),
      m_Width(f_width),
      m_Height(f_height)
    {}
  };

  // Interface representing a desktop system based window
  class BaseWindow
  {
    public:
      using EventCallbackfn = std::function<void(Engine::Events::Event&)>;

      virtual ~BaseWindow() = default;

      virtual void OnUpdate() = 0;

      virtual uint32_t GetWidth() const = 0;
      virtual uint32_t GetHeight() const = 0;

      // Window attributes
      virtual void SetEventCallback(const EventCallbackfn& f_callback) = 0;
      virtual void SetVSync(bool f_enabled) = 0;
      virtual bool IsVSync() const = 0;

      virtual void* GetNativeWindow() const = 0;

      static Scope<BaseWindow> Create(const WindowProps& f_props = WindowProps());
  };
} // namespace Engine::Core
