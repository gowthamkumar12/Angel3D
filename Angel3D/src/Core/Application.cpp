#include "Core/Application.h"
#include "Core/Log.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Windows/Input.h"
#include "glad/glad.h"

namespace Angel3D::Core
{
	Application* Application::m_ApplicationInstance = nullptr;

	Application::Application()
	{
		ANGEL3D_CORE_ASSERT(!m_ApplicationInstance, "Core application already exists.");
		m_ApplicationInstance = this;

		m_Window = std::unique_ptr<Angel3D::Core::BaseWindow>(Angel3D::Core::BaseWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		// Creating a new ImGui Layer and pushing it to the layer stack as a overlay.
		m_ImGuiLayer = new Angel3D::ImGuiImpl::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for(Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* f_layer)
	{
		m_LayerStack.PushLayer(f_layer);
		f_layer->OnAttach();
	}

	void Application::PushOverlay(Layer* f_overlay)
	{
		m_LayerStack.PushOverlay(f_overlay);
		f_overlay->OnAttach();
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