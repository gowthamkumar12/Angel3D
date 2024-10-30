#pragma once

#include "Core.h"

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
			};

			// To be defined in the CLIENT
			Application* CreateApplication();
	}
}

