#pragma once

namespace Angel3D::Core
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
#define ANGEL3D_KEY_SPACE              Angel3D::Core::KeyCode::Space
#define ANGEL3D_KEY_APOSTROPHE         Angel3D::Core::KeyCode::Apostrophe  /* ' */
#define ANGEL3D_KEY_COMMA              Angel3D::Core::KeyCode::Comma  /* , */
#define ANGEL3D_KEY_MINUS              Angel3D::Core::KeyCode::Minus  /* - */
#define ANGEL3D_KEY_PERIOD             Angel3D::Core::KeyCode::Period  /* . */
#define ANGEL3D_KEY_SLASH              Angel3D::Core::KeyCode::Slash  /* / */
#define ANGEL3D_KEY_0                  Angel3D::Core::KeyCode::Key0
#define ANGEL3D_KEY_1                  Angel3D::Core::KeyCode::Key1
#define ANGEL3D_KEY_2                  Angel3D::Core::KeyCode::Key2
#define ANGEL3D_KEY_3                  Angel3D::Core::KeyCode::Key3
#define ANGEL3D_KEY_4                  Angel3D::Core::KeyCode::Key4
#define ANGEL3D_KEY_5                  Angel3D::Core::KeyCode::Key5
#define ANGEL3D_KEY_6                  Angel3D::Core::KeyCode::Key6
#define ANGEL3D_KEY_7                  Angel3D::Core::KeyCode::Key7
#define ANGEL3D_KEY_8                  Angel3D::Core::KeyCode::Key8
#define ANGEL3D_KEY_9                  Angel3D::Core::KeyCode::Key9
#define ANGEL3D_KEY_SEMICOLON          Angel3D::Core::KeyCode::Semicolon  /* ; */
#define ANGEL3D_KEY_EQUAL              Angel3D::Core::KeyCode::Equal  /* = */
#define ANGEL3D_KEY_A                  Angel3D::Core::KeyCode::A
#define ANGEL3D_KEY_B                  Angel3D::Core::KeyCode::B
#define ANGEL3D_KEY_C                  Angel3D::Core::KeyCode::C
#define ANGEL3D_KEY_D                  Angel3D::Core::KeyCode::D
#define ANGEL3D_KEY_E                  Angel3D::Core::KeyCode::E
#define ANGEL3D_KEY_F                  Angel3D::Core::KeyCode::F
#define ANGEL3D_KEY_G                  Angel3D::Core::KeyCode::G
#define ANGEL3D_KEY_H                  Angel3D::Core::KeyCode::H
#define ANGEL3D_KEY_I                  Angel3D::Core::KeyCode::I
#define ANGEL3D_KEY_J                  Angel3D::Core::KeyCode::J
#define ANGEL3D_KEY_K                  Angel3D::Core::KeyCode::K
#define ANGEL3D_KEY_L                  Angel3D::Core::KeyCode::L
#define ANGEL3D_KEY_M                  Angel3D::Core::KeyCode::M
#define ANGEL3D_KEY_N                  Angel3D::Core::KeyCode::N
#define ANGEL3D_KEY_O                  Angel3D::Core::KeyCode::O
#define ANGEL3D_KEY_P                  Angel3D::Core::KeyCode::P
#define ANGEL3D_KEY_Q                  Angel3D::Core::KeyCode::Q
#define ANGEL3D_KEY_R                  Angel3D::Core::KeyCode::R
#define ANGEL3D_KEY_S                  Angel3D::Core::KeyCode::S
#define ANGEL3D_KEY_T                  Angel3D::Core::KeyCode::T
#define ANGEL3D_KEY_U                  Angel3D::Core::KeyCode::U
#define ANGEL3D_KEY_V                  Angel3D::Core::KeyCode::V
#define ANGEL3D_KEY_W                  Angel3D::Core::KeyCode::W
#define ANGEL3D_KEY_X                  Angel3D::Core::KeyCode::X
#define ANGEL3D_KEY_Y                  Angel3D::Core::KeyCode::Y
#define ANGEL3D_KEY_Z                  Angel3D::Core::KeyCode::Z
#define ANGEL3D_KEY_LEFT_BRACKET       Angel3D::Core::KeyCode::LeftBracket  /* [ */
#define ANGEL3D_KEY_BACKSLASH          Angel3D::Core::KeyCode::Backslash  /* \ */
#define ANGEL3D_KEY_RIGHT_BRACKET      Angel3D::Core::KeyCode::RightBracket  /* ] */
#define ANGEL3D_KEY_GRAVE_ACCENT       Angel3D::Core::KeyCode::GraveAccent  /* ` */
#define ANGEL3D_KEY_WORLD_1            Angel3D::Core::KeyCode::World1 /* non-US #1 */
#define ANGEL3D_KEY_WORLD_2            Angel3D::Core::KeyCode::World2 /* non-US #2 */

/* Function keys */
#define ANGEL3D_KEY_ESCAPE             Angel3D::Core::KeyCode::Escape
#define ANGEL3D_KEY_ENTER              Angel3D::Core::KeyCode::Enter
#define ANGEL3D_KEY_TAB                Angel3D::Core::KeyCode::Tab
#define ANGEL3D_KEY_BACKSPACE          Angel3D::Core::KeyCode::Backspace
#define ANGEL3D_KEY_INSERT             Angel3D::Core::KeyCode::Insert
#define ANGEL3D_KEY_DELETE             Angel3D::Core::KeyCode::Delete
#define ANGEL3D_KEY_RIGHT              Angel3D::Core::KeyCode::Right
#define ANGEL3D_KEY_LEFT               Angel3D::Core::KeyCode::Left
#define ANGEL3D_KEY_DOWN               Angel3D::Core::KeyCode::Down
#define ANGEL3D_KEY_UP                 Angel3D::Core::KeyCode::Up
#define ANGEL3D_KEY_PAGE_UP            Angel3D::Core::KeyCode::PageUp
#define ANGEL3D_KEY_PAGE_DOWN          Angel3D::Core::KeyCode::PageDown
#define ANGEL3D_KEY_HOME               Angel3D::Core::KeyCode::Home
#define ANGEL3D_KEY_END                Angel3D::Core::KeyCode::End
#define ANGEL3D_KEY_CAPS_LOCK          Angel3D::Core::KeyCode::CapsLock
#define ANGEL3D_KEY_SCROLL_LOCK        Angel3D::Core::KeyCode::ScrollLock
#define ANGEL3D_KEY_NUM_LOCK           Angel3D::Core::KeyCode::NumLock
#define ANGEL3D_KEY_PRINT_SCREEN       Angel3D::Core::KeyCode::PrintScreen
#define ANGEL3D_KEY_PAUSE              Angel3D::Core::KeyCode::Pause
#define ANGEL3D_KEY_F1                 Angel3D::Core::KeyCode::F1
#define ANGEL3D_KEY_F2                 Angel3D::Core::KeyCode::F2
#define ANGEL3D_KEY_F3                 Angel3D::Core::KeyCode::F3
#define ANGEL3D_KEY_F4                 Angel3D::Core::KeyCode::F4
#define ANGEL3D_KEY_F5                 Angel3D::Core::KeyCode::F5
#define ANGEL3D_KEY_F6                 Angel3D::Core::KeyCode::F6
#define ANGEL3D_KEY_F7                 Angel3D::Core::KeyCode::F7
#define ANGEL3D_KEY_F8                 Angel3D::Core::KeyCode::F8
#define ANGEL3D_KEY_F9                 Angel3D::Core::KeyCode::F9
#define ANGEL3D_KEY_F10                Angel3D::Core::KeyCode::F10
#define ANGEL3D_KEY_F11                Angel3D::Core::KeyCode::F11
#define ANGEL3D_KEY_F12                Angel3D::Core::KeyCode::F12
#define ANGEL3D_KEY_F13                Angel3D::Core::KeyCode::F13
#define ANGEL3D_KEY_F14                Angel3D::Core::KeyCode::F14
#define ANGEL3D_KEY_F15                Angel3D::Core::KeyCode::F15
#define ANGEL3D_KEY_F16                Angel3D::Core::KeyCode::F16
#define ANGEL3D_KEY_F17                Angel3D::Core::KeyCode::F17
#define ANGEL3D_KEY_F18                Angel3D::Core::KeyCode::F18
#define ANGEL3D_KEY_F19                Angel3D::Core::KeyCode::F19
#define ANGEL3D_KEY_F20                Angel3D::Core::KeyCode::F20
#define ANGEL3D_KEY_F21                Angel3D::Core::KeyCode::F21
#define ANGEL3D_KEY_F22                Angel3D::Core::KeyCode::F22
#define ANGEL3D_KEY_F23                Angel3D::Core::KeyCode::F23
#define ANGEL3D_KEY_F24                Angel3D::Core::KeyCode::F24
#define ANGEL3D_KEY_F25                Angel3D::Core::KeyCode::F25
#define ANGEL3D_KEY_KP_0               Angel3D::Core::KeyCode::KP_0
#define ANGEL3D_KEY_KP_1               Angel3D::Core::KeyCode::KP_1
#define ANGEL3D_KEY_KP_2               Angel3D::Core::KeyCode::KP_2
#define ANGEL3D_KEY_KP_3               Angel3D::Core::KeyCode::KP_3
#define ANGEL3D_KEY_KP_4               Angel3D::Core::KeyCode::KP_4
#define ANGEL3D_KEY_KP_5               Angel3D::Core::KeyCode::KP_5
#define ANGEL3D_KEY_KP_6               Angel3D::Core::KeyCode::KP_6
#define ANGEL3D_KEY_KP_7               Angel3D::Core::KeyCode::KP_7
#define ANGEL3D_KEY_KP_8               Angel3D::Core::KeyCode::KP_8
#define ANGEL3D_KEY_KP_9               Angel3D::Core::KeyCode::KP_9
#define ANGEL3D_KEY_KP_DECIMAL         Angel3D::Core::KeyCode::KP_Decimal
#define ANGEL3D_KEY_KP_DIVIDE          Angel3D::Core::KeyCode::KP_Divide
#define ANGEL3D_KEY_KP_MULTIPLY        Angel3D::Core::KeyCode::KP_Multiply
#define ANGEL3D_KEY_KP_SUBTRACT        Angel3D::Core::KeyCode::KP_Subtract
#define ANGEL3D_KEY_KP_ADD             Angel3D::Core::KeyCode::KP_Add
#define ANGEL3D_KEY_KP_ENTER           Angel3D::Core::KeyCode::KP_Enter
#define ANGEL3D_KEY_KP_EQUAL           Angel3D::Core::KeyCode::KP_Equal
#define ANGEL3D_KEY_LEFT_SHIFT         Angel3D::Core::KeyCode::LeftShift
#define ANGEL3D_KEY_LEFT_CONTROL       Angel3D::Core::KeyCode::LeftControl
#define ANGEL3D_KEY_LEFT_ALT           Angel3D::Core::KeyCode::LeftAlt
#define ANGEL3D_KEY_LEFT_SUPER         Angel3D::Core::KeyCode::LeftSuper
#define ANGEL3D_KEY_RIGHT_SHIFT        Angel3D::Core::KeyCode::RightShift
#define ANGEL3D_KEY_RIGHT_CONTROL      Angel3D::Core::KeyCode::RightControl
#define ANGEL3D_KEY_RIGHT_ALT          Angel3D::Core::KeyCode::RightAlt
#define ANGEL3D_KEY_RIGHT_SUPER        Angel3D::Core::KeyCode::RightSuper
#define ANGEL3D_KEY_MENU               Angel3D::Core::KeyCode::Menu