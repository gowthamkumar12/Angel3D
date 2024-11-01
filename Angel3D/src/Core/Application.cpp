#include "Core/Application.h"
#include "Events/ApplicationEvent.h"

#include "Core/Log.h"

#include "glad/glad.h"

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

		void Application::Run()
		{
			while (m_Running)
			{
				glClearColor(0, 1, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				for(Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}

				m_Window->OnUpdate();
			}
		}

		void Application::PushLayer(Layer* f_layer)
		{
			m_LayerStack.PushLayer(f_layer);
		}

		void Application::PushOverlay(Layer* f_overlay)
		{
			m_LayerStack.PushOverlay(f_overlay);
		}

		void Application::OnEvent(Angel3D::Events::Event& f_e)
		{
			Events::EventDispatcher dispatcher(f_e);
			dispatcher.Dispatch<Events::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

			ANGEL3D_CORE_TRACE("{0}", f_e.ToString());

			for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
			{
				(*--it)->OnEvent(f_e);
				if(f_e.m_Handled);
				{
					break;
				}
			}
		}

		bool Application::OnWindowClose(Events::WindowCloseEvent& f_events)
		{
			m_Running = false;
			return true;
		}
	}
}