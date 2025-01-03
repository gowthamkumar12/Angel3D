#pragma once

namespace Angel3D::Core
{
  enum class MouseCode : uint16_t
  {
    Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,
		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
  };
} // namespace Angel3D::Core::MouseKey

#define ANGEL3D_MOUSE_BUTTON_1         Angel3D::Core::MouseCode::Button0
#define ANGEL3D_MOUSE_BUTTON_2         Angel3D::Core::MouseCode::Button1
#define ANGEL3D_MOUSE_BUTTON_3         Angel3D::Core::MouseCode::Button2
#define ANGEL3D_MOUSE_BUTTON_4         Angel3D::Core::MouseCode::Button3
#define ANGEL3D_MOUSE_BUTTON_5         Angel3D::Core::MouseCode::Button4
#define ANGEL3D_MOUSE_BUTTON_6         Angel3D::Core::MouseCode::Button5
#define ANGEL3D_MOUSE_BUTTON_7         Angel3D::Core::MouseCode::Button6
#define ANGEL3D_MOUSE_BUTTON_8         Angel3D::Core::MouseCode::Button7
#define ANGEL3D_MOUSE_BUTTON_LAST      Angel3D::Core::MouseCode::ButtonLast
#define ANGEL3D_MOUSE_BUTTON_LEFT      Angel3D::Core::MouseCode::ButtonLeft
#define ANGEL3D_MOUSE_BUTTON_RIGHT     Angel3D::Core::MouseCode::ButtonRight
#define ANGEL3D_MOUSE_BUTTON_MIDDLE    Angel3D::Core::MouseCode::ButtonMiddle