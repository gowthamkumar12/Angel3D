#pragma once

#include "pch.h"
#include "Core/BaseWindow.h"
#include "Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Angel3D::Platform::Windows
{
  class ANGEL3D_API Window : public Angel3D::Core::BaseWindow
  {
    public:
      Window(const Angel3D::Core::WindowProps& f_props);
      virtual ~Window();

      virtual void OnUpdate() override;

      virtual inline unsigned int GetWidth() const override { return m_data.m_Width; }
      virtual inline unsigned int GetHeight() const override { return m_data.m_Height; }

      virtual inline void SetEventCallback(const EventCallbackfn& f_callback) override { m_data.m_eventCallbackFn = f_callback; }
      virtual void SetVSync(bool f_enabled) override;
      virtual bool IsVSync() const override;
      virtual inline void* GetNativeWindow() const override { return m_window; }

    private:
      virtual void Init(const Angel3D::Core::WindowProps& f_props);
      virtual void Shutdown();

      GLFWwindow* m_window;

      Angel3D::Renderer::GraphicsContext* m_Context;

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
