#pragma once

#include "Core.h"
#include "Platform/Windows/Window.h"

namespace Angel3D
{
	namespace Core
	{
		class ANGEL3D_API Application
		{
			public:
				Application();
				~Application();
				void Run();

			private:
				std::unique_ptr<Angel3D::Core::BaseWindow> m_Window;
				bool m_Running = true;
			};

			// To be defined in the CLIENT
			Application* CreateApplication();
	}
}