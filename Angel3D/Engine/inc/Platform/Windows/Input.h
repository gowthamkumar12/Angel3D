#pragma once

#include "pch.h"
#include "Core/Core.h"
#include "Core/Input.h"

namespace Engine::Platform::Windows
{
  class WindowsInput : public Engine::Core::Input
  {
    protected:
      virtual bool IsKeyPressedImpl(Engine::Core::KeyCode f_keycode)           override;
      virtual std::pair<float, float> GetMousePositionImpl() override;
      virtual bool IsMouseButtonPressedImpl(Engine::Core::MouseCode f_button)    override;
      virtual float GetMouseXImpl()                          override;
      virtual float GetMouseYImpl()                          override;
  };
} // namespace Engine::Platform::Windows
