#include "Core/BaseWindow.h"

#ifdef PLATFORM_WINDOWS
	#include "Platform/Windows/Window.h"
#endif

namespace Engine::Core
{
	Scope<BaseWindow> BaseWindow::Create(const WindowProps& props)
	{
    #ifdef PLATFORM_WINDOWS
      return CreateScope<Engine::Platform::Windows::Window>(props);
    #else
      CORE_ASSERT(false, "Unknown platform!");
      return nullptr;
  	#endif
	}
}