#include "Core/Application.h"
#include "Events/ApplicationEvent.h"

#include "Core/Log.h"

namespace Angel3D
{
	namespace Core
	{
		#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
		Application::Application()
		{
			m_Window = std::unique_ptr<Angel3D::Core::BaseWindow>(Angel3D::Core::BaseWindow::Create());
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		}

		Application::~Application()
		{
		}

		void Application::OnEvent(Angel3D::Events::Event& f_e)
		{
			Events::EventDispatcher dispatcher(f_e);
			dispatcher.Dispatch<Events::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

			ANGEL3D_CORE_TRACE("{0}", f_e.ToString());
		}

		void Application::Run()
		{
			while (m_Running)
			{
				glClearColor(0, 1, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				m_Window->OnUpdate();
			}
		}

		bool Application::OnWindowClose(Events::WindowCloseEvent& f_events)
		{
			m_Running = false;
			return true;
		}
	}
}