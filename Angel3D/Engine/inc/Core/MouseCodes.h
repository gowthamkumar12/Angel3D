#pragma once

namespace Engine::Core
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
} // namespace Engine::Core::MouseKey

#define MOUSE_BUTTON_1         Engine::Core::MouseCode::Button0
#define MOUSE_BUTTON_2         Engine::Core::MouseCode::Button1
#define MOUSE_BUTTON_3         Engine::Core::MouseCode::Button2
#define MOUSE_BUTTON_4         Engine::Core::MouseCode::Button3
#define MOUSE_BUTTON_5         Engine::Core::MouseCode::Button4
#define MOUSE_BUTTON_6         Engine::Core::MouseCode::Button5
#define MOUSE_BUTTON_7         Engine::Core::MouseCode::Button6
#define MOUSE_BUTTON_8         Engine::Core::MouseCode::Button7
#define MOUSE_BUTTON_LAST      Engine::Core::MouseCode::ButtonLast
#define MOUSE_BUTTON_LEFT      Engine::Core::MouseCode::ButtonLeft
#define MOUSE_BUTTON_RIGHT     Engine::Core::MouseCode::ButtonRight
#define MOUSE_BUTTON_MIDDLE    Engine::Core::MouseCode::ButtonMiddle