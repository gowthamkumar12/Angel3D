#pragma once

#include "Core/Log.h"
#include "Core/Core.h"

#ifdef ANGEL3D_PLATFORM_WINDOWS
	extern Angel3D::Core::Application* Angel3D::Core::CreateApplication();

	int main(int argc, char** argv)
	{
		Angel3D::Core::Log::Init();

		ANGEL3D_PROFILE_BEGIN_SESSION("Startup", "Startup_profile.json");
		auto app = Angel3D::Core::CreateApplication();
		ANGEL3D_PROFILE_END_SESSION();

		ANGEL3D_PROFILE_BEGIN_SESSION("Runtime", "Runtime_profile.json");
		app->Run();
		ANGEL3D_PROFILE_END_SESSION();

		ANGEL3D_PROFILE_BEGIN_SESSION("Shutdown", "Shutdown_profile.json");
		delete app;
		ANGEL3D_PROFILE_END_SESSION();
	}
#else
	#error Angel3D only supports Windows!
#endif // ANGEL3D_PLATFORM_WINDOWS
