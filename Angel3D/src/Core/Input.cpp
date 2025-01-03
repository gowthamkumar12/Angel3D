#include "Core/Input.h"

#ifdef ANGEL3D_PLATFORM_WINDOWS
	#include "Platform/Windows/Input.h"
#endif

namespace Angel3D::Core
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
    #ifdef ANGEL3D_PLATFORM_WINDOWS
      return CreateScope<Angel3D::Platform::Windows::WindowsInput>();
    #else
      ANGEL3D_CORE_ASSERT(false, "Unknown platform!");
      return nullptr;
    #endif
	}
}