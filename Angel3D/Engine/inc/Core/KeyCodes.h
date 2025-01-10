#pragma once

namespace Engine::Core
{
  enum class KeyCode : uint16_t
  {
    // Printable keys
    Space           = 32,
    Apostrophe      = 39,  // '
    Comma           = 44,  // ,
    Minus           = 45,  // -
    Period          = 46,  // .
    Slash           = 47,  // /
    Key0            = 48,
    Key1            = 49,
    Key2            = 50,
    Key3            = 51,
    Key4            = 52,
    Key5            = 53,
    Key6            = 54,
    Key7            = 55,
    Key8            = 56,
    Key9            = 57,
    Semicolon       = 59,  // ;
    Equal           = 61,  // =
    A               = 65,
    B               = 66,
    C               = 67,
    D               = 68,
    E               = 69,
    F               = 70,
    G               = 71,
    H               = 72,
    I               = 73,
    J               = 74,
    K               = 75,
    L               = 76,
    M               = 77,
    N               = 78,
    O               = 79,
    P               = 80,
    Q               = 81,
    R               = 82,
    S               = 83,
    T               = 84,
    U               = 85,
    V               = 86,
    W               = 87,
    X               = 88,
    Y               = 89,
    Z               = 90,
    LeftBracket     = 91,  // [
    Backslash       = 92,  /* \ */
    RightBracket    = 93,  // ]
    GraveAccent     = 96,  // `
    World1          = 161, // non-US #1
    World2          = 162, // non-US #2

    // Function keys
    Escape          = 256,
    Enter           = 257,
    Tab             = 258,
    Backspace       = 259,
    Insert          = 260,
    Delete          = 261,
    Right           = 262,
    Left            = 263,
    Down            = 264,
    Up              = 265,
    PageUp          = 266,
    PageDown        = 267,
    Home            = 268,
    End             = 269,
    CapsLock        = 280,
    ScrollLock      = 281,
    NumLock         = 282,
    PrintScreen     = 283,
    Pause           = 284,
    F1              = 290,
    F2              = 291,
    F3              = 292,
    F4              = 293,
    F5              = 294,
    F6              = 295,
    F7              = 296,
    F8              = 297,
    F9              = 298,
    F10             = 299,
    F11             = 300,
    F12             = 301,
    F13             = 302,
    F14             = 303,
    F15             = 304,
    F16             = 305,
    F17             = 306,
    F18             = 307,
    F19             = 308,
    F20             = 309,
    F21             = 310,
    F22             = 311,
    F23             = 312,
    F24             = 313,
    F25             = 314,
    KP_0            = 320,
    KP_1            = 321,
    KP_2            = 322,
    KP_3            = 323,
    KP_4            = 324,
    KP_5            = 325,
    KP_6            = 326,
    KP_7            = 327,
    KP_8            = 328,
    KP_9            = 329,
    KP_Decimal      = 330,
    KP_Divide       = 331,
    KP_Multiply     = 332,
    KP_Subtract     = 333,
    KP_Add          = 334,
    KP_Enter        = 335,
    KP_Equal        = 336,
    LeftShift       = 340,
    LeftControl     = 341,
    LeftAlt         = 342,
    LeftSuper       = 343,
    RightShift      = 344,
    RightControl    = 345,
    RightAlt        = 346,
    RightSuper      = 347,
    Menu            = 348
  };
}

/* Printable keys */
#define KEY_SPACE              Engine::Core::KeyCode::Space
#define KEY_APOSTROPHE         Engine::Core::KeyCode::Apostrophe  /* ' */
#define KEY_COMMA              Engine::Core::KeyCode::Comma  /* , */
#define KEY_MINUS              Engine::Core::KeyCode::Minus  /* - */
#define KEY_PERIOD             Engine::Core::KeyCode::Period  /* . */
#define KEY_SLASH              Engine::Core::KeyCode::Slash  /* / */
#define KEY_0                  Engine::Core::KeyCode::Key0
#define KEY_1                  Engine::Core::KeyCode::Key1
#define KEY_2                  Engine::Core::KeyCode::Key2
#define KEY_3                  Engine::Core::KeyCode::Key3
#define KEY_4                  Engine::Core::KeyCode::Key4
#define KEY_5                  Engine::Core::KeyCode::Key5
#define KEY_6                  Engine::Core::KeyCode::Key6
#define KEY_7                  Engine::Core::KeyCode::Key7
#define KEY_8                  Engine::Core::KeyCode::Key8
#define KEY_9                  Engine::Core::KeyCode::Key9
#define KEY_SEMICOLON          Engine::Core::KeyCode::Semicolon  /* ; */
#define KEY_EQUAL              Engine::Core::KeyCode::Equal  /* = */
#define KEY_A                  Engine::Core::KeyCode::A
#define KEY_B                  Engine::Core::KeyCode::B
#define KEY_C                  Engine::Core::KeyCode::C
#define KEY_D                  Engine::Core::KeyCode::D
#define KEY_E                  Engine::Core::KeyCode::E
#define KEY_F                  Engine::Core::KeyCode::F
#define KEY_G                  Engine::Core::KeyCode::G
#define KEY_H                  Engine::Core::KeyCode::H
#define KEY_I                  Engine::Core::KeyCode::I
#define KEY_J                  Engine::Core::KeyCode::J
#define KEY_K                  Engine::Core::KeyCode::K
#define KEY_L                  Engine::Core::KeyCode::L
#define KEY_M                  Engine::Core::KeyCode::M
#define KEY_N                  Engine::Core::KeyCode::N
#define KEY_O                  Engine::Core::KeyCode::O
#define KEY_P                  Engine::Core::KeyCode::P
#define KEY_Q                  Engine::Core::KeyCode::Q
#define KEY_R                  Engine::Core::KeyCode::R
#define KEY_S                  Engine::Core::KeyCode::S
#define KEY_T                  Engine::Core::KeyCode::T
#define KEY_U                  Engine::Core::KeyCode::U
#define KEY_V                  Engine::Core::KeyCode::V
#define KEY_W                  Engine::Core::KeyCode::W
#define KEY_X                  Engine::Core::KeyCode::X
#define KEY_Y                  Engine::Core::KeyCode::Y
#define KEY_Z                  Engine::Core::KeyCode::Z
#define KEY_LEFT_BRACKET       Engine::Core::KeyCode::LeftBracket  /* [ */
#define KEY_BACKSLASH          Engine::Core::KeyCode::Backslash  /* \ */
#define KEY_RIGHT_BRACKET      Engine::Core::KeyCode::RightBracket  /* ] */
#define KEY_GRAVE_ACCENT       Engine::Core::KeyCode::GraveAccent  /* ` */
#define KEY_WORLD_1            Engine::Core::KeyCode::World1 /* non-US #1 */
#define KEY_WORLD_2            Engine::Core::KeyCode::World2 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             Engine::Core::KeyCode::Escape
#define KEY_ENTER              Engine::Core::KeyCode::Enter
#define KEY_TAB                Engine::Core::KeyCode::Tab
#define KEY_BACKSPACE          Engine::Core::KeyCode::Backspace
#define KEY_INSERT             Engine::Core::KeyCode::Insert
#define KEY_DELETE             Engine::Core::KeyCode::Delete
#define KEY_RIGHT              Engine::Core::KeyCode::Right
#define KEY_LEFT               Engine::Core::KeyCode::Left
#define KEY_DOWN               Engine::Core::KeyCode::Down
#define KEY_UP                 Engine::Core::KeyCode::Up
#define KEY_PAGE_UP            Engine::Core::KeyCode::PageUp
#define KEY_PAGE_DOWN          Engine::Core::KeyCode::PageDown
#define KEY_HOME               Engine::Core::KeyCode::Home
#define KEY_END                Engine::Core::KeyCode::End
#define KEY_CAPS_LOCK          Engine::Core::KeyCode::CapsLock
#define KEY_SCROLL_LOCK        Engine::Core::KeyCode::ScrollLock
#define KEY_NUM_LOCK           Engine::Core::KeyCode::NumLock
#define KEY_PRINT_SCREEN       Engine::Core::KeyCode::PrintScreen
#define KEY_PAUSE              Engine::Core::KeyCode::Pause
#define KEY_F1                 Engine::Core::KeyCode::F1
#define KEY_F2                 Engine::Core::KeyCode::F2
#define KEY_F3                 Engine::Core::KeyCode::F3
#define KEY_F4                 Engine::Core::KeyCode::F4
#define KEY_F5                 Engine::Core::KeyCode::F5
#define KEY_F6                 Engine::Core::KeyCode::F6
#define KEY_F7                 Engine::Core::KeyCode::F7
#define KEY_F8                 Engine::Core::KeyCode::F8
#define KEY_F9                 Engine::Core::KeyCode::F9
#define KEY_F10                Engine::Core::KeyCode::F10
#define KEY_F11                Engine::Core::KeyCode::F11
#define KEY_F12                Engine::Core::KeyCode::F12
#define KEY_F13                Engine::Core::KeyCode::F13
#define KEY_F14                Engine::Core::KeyCode::F14
#define KEY_F15                Engine::Core::KeyCode::F15
#define KEY_F16                Engine::Core::KeyCode::F16
#define KEY_F17                Engine::Core::KeyCode::F17
#define KEY_F18                Engine::Core::KeyCode::F18
#define KEY_F19                Engine::Core::KeyCode::F19
#define KEY_F20                Engine::Core::KeyCode::F20
#define KEY_F21                Engine::Core::KeyCode::F21
#define KEY_F22                Engine::Core::KeyCode::F22
#define KEY_F23                Engine::Core::KeyCode::F23
#define KEY_F24                Engine::Core::KeyCode::F24
#define KEY_F25                Engine::Core::KeyCode::F25
#define KEY_KP_0               Engine::Core::KeyCode::KP_0
#define KEY_KP_1               Engine::Core::KeyCode::KP_1
#define KEY_KP_2               Engine::Core::KeyCode::KP_2
#define KEY_KP_3               Engine::Core::KeyCode::KP_3
#define KEY_KP_4               Engine::Core::KeyCode::KP_4
#define KEY_KP_5               Engine::Core::KeyCode::KP_5
#define KEY_KP_6               Engine::Core::KeyCode::KP_6
#define KEY_KP_7               Engine::Core::KeyCode::KP_7
#define KEY_KP_8               Engine::Core::KeyCode::KP_8
#define KEY_KP_9               Engine::Core::KeyCode::KP_9
#define KEY_KP_DECIMAL         Engine::Core::KeyCode::KP_Decimal
#define KEY_KP_DIVIDE          Engine::Core::KeyCode::KP_Divide
#define KEY_KP_MULTIPLY        Engine::Core::KeyCode::KP_Multiply
#define KEY_KP_SUBTRACT        Engine::Core::KeyCode::KP_Subtract
#define KEY_KP_ADD             Engine::Core::KeyCode::KP_Add
#define KEY_KP_ENTER           Engine::Core::KeyCode::KP_Enter
#define KEY_KP_EQUAL           Engine::Core::KeyCode::KP_Equal
#define KEY_LEFT_SHIFT         Engine::Core::KeyCode::LeftShift
#define KEY_LEFT_CONTROL       Engine::Core::KeyCode::LeftControl
#define KEY_LEFT_ALT           Engine::Core::KeyCode::LeftAlt
#define KEY_LEFT_SUPER         Engine::Core::KeyCode::LeftSuper
#define KEY_RIGHT_SHIFT        Engine::Core::KeyCode::RightShift
#define KEY_RIGHT_CONTROL      Engine::Core::KeyCode::RightControl
#define KEY_RIGHT_ALT          Engine::Core::KeyCode::RightAlt
#define KEY_RIGHT_SUPER        Engine::Core::KeyCode::RightSuper
#define KEY_MENU               Engine::Core::KeyCode::Menu