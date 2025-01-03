#pragma once

#include "Core/Core.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

namespace Angel3D::Core
{
  class Input
  {
    public:
      // Polling the key pressed events
      inline static bool IsKeyPressed(KeyCode f_keycode) { return s_Instance->IsKeyPressedImpl(f_keycode); }

      // Polling the mouse events
      inline static bool IsMouseButtonPressed(MouseCode f_button) { return s_Instance->IsMouseButtonPressedImpl(f_button); }
      inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
      inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
      inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

      static Scope<Input> Create();

    protected:
      virtual bool IsKeyPressedImpl(KeyCode f_keycode) = 0;

      virtual bool IsMouseButtonPressedImpl(MouseCode f_button) = 0;
      virtual std::pair<float, float> GetMousePositionImpl() = 0;
      virtual float GetMouseXImpl() = 0;
      virtual float GetMouseYImpl() = 0;

    private:
      static Scope<Input> s_Instance;
  };
} // namespace Angel3D::Core
