#pragma once

#include "Core/Log.h"
#include "Core/Core.h"

#ifdef PLATFORM_WINDOWS
	extern Engine::Core::Application* Engine::Core::CreateApplication();

	int main(int argc, char** argv)
	{
		Engine::Core::Log::Init();

		PROFILE_BEGIN_SESSION("Startup", "Startup_profile.json");
		auto app = Engine::Core::CreateApplication();
		PROFILE_END_SESSION();

		PROFILE_BEGIN_SESSION("Runtime", "Runtime_profile.json");
		app->Run();
		PROFILE_END_SESSION();

		PROFILE_BEGIN_SESSION("Shutdown", "Shutdown_profile.json");
		delete app;
		PROFILE_END_SESSION();
	}
#else
	#error Engine only supports Windows!
#endif // PLATFORM_WINDOWS
