#include "Core/Application.h"
#include "Events/ApplicationEvent.h"
#include "Core/Log.h"

namespace Angel3D
{
	namespace Core
	{
		Application::Application()
		{
			m_Window = std::unique_ptr<Angel3D::Core::BaseWindow>(Angel3D::Core::BaseWindow::Create());
		}

		Application::~Application()
		{}

		void Application::Run()
		{
			while (m_Running)
			{
				glClearColor(0, 1, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				m_Window->OnUpdate();
			}
		}
	}
}