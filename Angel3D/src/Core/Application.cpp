#include "Core/Application.h"
#include "Events/ApplicationEvent.h"
#include "Core/Log.h"
namespace Angel3D
{
	namespace Core
	{
		Application::Application()
		{}

		Application::~Application()
		{}

		void Application::Run()
		{
			Angel3D::Events::WindowResizeEvent e(1280, 720);
			ANGEL3D_TRACE(e.ToString());
			while (true);
		}
	}
}