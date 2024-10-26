#pragma once

#ifdef ANGEL3D_PLATFORM_WINDOWS
	extern Angel3D::Core::Application* Angel3D::Core::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = Angel3D::Core::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Angel3D only supports Windows!
#endif // ANGEL3D_PLATFORM_WINDOWS
