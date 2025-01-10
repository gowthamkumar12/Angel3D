#include "Core/Input.h"

#ifdef PLATFORM_WINDOWS
	#include "Platform/Windows/Input.h"
#endif

namespace Engine::Core
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
    #ifdef PLATFORM_WINDOWS
      return CreateScope<Engine::Platform::Windows::WindowsInput>();
    #else
      CORE_ASSERT(false, "Unknown platform!");
      return nullptr;
    #endif
	}
}