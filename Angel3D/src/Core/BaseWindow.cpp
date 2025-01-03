#include "Core/BaseWindow.h"

#ifdef ANGEL3D_PLATFORM_WINDOWS
	#include "Platform/Windows/Window.h"
#endif

namespace Angel3D::Core
{
	Scope<BaseWindow> BaseWindow::Create(const WindowProps& props)
	{
    #ifdef ANGEL3D_PLATFORM_WINDOWS
      return CreateScope<Angel3D::Platform::Windows::Window>(props);
    #else
      ANGEL3D_CORE_ASSERT(false, "Unknown platform!");
      return nullptr;
  	#endif
	}
}