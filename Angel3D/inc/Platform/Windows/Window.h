#pragma once

#include "Core/BaseWindow.h"
#include <GLFW/glfw3.h>

namespace Angel3D::Platform::Windows
{
  class ANGEL3D_API Window : public Angel3D::Core::BaseWindow
  {
    public:
      Window(const Angel3D::Core::WindowProps& f_props);
      virtual ~Window();

      void OnUpdate() override;

      inline unsigned int GetWidth() const override { return m_data.m_Width; }
      inline unsigned int GetHeight() const override { return m_data.m_Height; }

      inline void SetEventCallback(const EventCallbackfn& f_callback) override { m_data.m_eventCallbackFn = f_callback; }
      void SetVSync(bool f_enabled) override;
      bool IsVSync() const override;
      inline void* GetNativeWindow() const override { return m_window; }

    private:
      virtual void Init(const Angel3D::Core::WindowProps& f_props);
      virtual void Shutdown();

      GLFWwindow* m_window;

      struct WindowData
      {
        std::string     m_Title;
        unsigned int    m_Width;
        unsigned int    m_Height;
        bool            m_vSync;
        EventCallbackfn m_eventCallbackFn;
      };

      WindowData m_data;
  };
} // namespace Angel3D
