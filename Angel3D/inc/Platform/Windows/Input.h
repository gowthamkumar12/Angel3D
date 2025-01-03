#pragma once

#include "pch.h"
#include "Core/Core.h"
#include "Core/Input.h"

namespace Angel3D::Platform::Windows
{
  class WindowsInput : public Angel3D::Core::Input
  {
    protected:
      virtual bool IsKeyPressedImpl(Angel3D::Core::KeyCode f_keycode)           override;
      virtual std::pair<float, float> GetMousePositionImpl() override;
      virtual bool IsMouseButtonPressedImpl(Angel3D::Core::MouseCode f_button)    override;
      virtual float GetMouseXImpl()                          override;
      virtual float GetMouseYImpl()                          override;
  };
} // namespace Angel3D::Platform::Windows
