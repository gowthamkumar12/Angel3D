#pragma once

#ifdef ANGEL3D_PLATFORM_WINDOWS
	extern Angel3D::Core::Application* Angel3D::Core::CreateApplication();

	int main(int argc, char** argv)
	{
		Angel3D::Core::Log::Init();

		ANGEL3D_CORE_ERROR("Hello");
		ANGEL3D_WARN("Hello");

		auto app = Angel3D::Core::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Angel3D only supports Windows!
#endif // ANGEL3D_PLATFORM_WINDOWS
