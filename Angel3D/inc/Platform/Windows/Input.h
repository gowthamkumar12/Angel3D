#pragma once

#include "Core/Core.h"
#include "Core/Input.h"

namespace Angel3D::Platform::Windows
{
  class WindowsInput : public Angel3D::Core::Input
  {
    protected:
      bool IsKeyPressedImpl(int f_keycode)           override;
      std::pair<float, float> GetMousePositionImpl() override;
      bool IsMouseButtonPressedImpl(int f_button)    override;
      float GetMouseXImpl()                          override;
      float GetMouseYImpl()                          override;
  };
} // namespace Angel3D::Platform::Windows
