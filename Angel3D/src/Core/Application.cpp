#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Windows/Input.h"
#include "Renderer/Renderer.h"

namespace Angel3D::Core
{
	Application* Application::m_ApplicationInstance = nullptr;

	Application::Application()
	{
		ANGEL3D_PROFILE_FUNCTION();

		ANGEL3D_CORE_ASSERT(!m_ApplicationInstance, "Core application already exists.");
		m_ApplicationInstance = this;

		m_Window = Angel3D::Core::BaseWindow::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Angel3D::Renderer::Renderer::Init();

		// Creating a new ImGui Layer and pushing it to the layer stack as a overlay.
		m_ImGuiLayer = CreateRef<Angel3D::ImGuiImpl::ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		ANGEL3D_PROFILE_FUNCTION();

		Angel3D::Renderer::Renderer::Shutdown();
	}

	void Application::PushLayer(Ref<Layer> f_layer)
	{
		ANGEL3D_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(f_layer);
		f_layer->OnAttach();
	}

	void Application::PushOverlay(Ref<Layer> f_overlay)
	{
		ANGEL3D_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(f_overlay);
		f_overlay->OnAttach();
	}

	void Application::OnEvent(Angel3D::Events::Event& f_e)
	{
		ANGEL3D_PROFILE_FUNCTION();

		Events::EventDispatcher dispatcher(f_e);
		dispatcher.Dispatch<Events::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<Events::WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for(auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if(f_e.m_Handled)
			{
				break;
			}
			(*it)->OnEvent(f_e);
		}
	}

	void Application::Run()
	{
		ANGEL3D_PROFILE_FUNCTION();

		while (m_Running)
		{
			ANGEL3D_PROFILE_SCOPE("Application::RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if(!m_Minimized)
			{
				{
					ANGEL3D_PROFILE_SCOPE("Application::LayerStack::OnUpdate");

					for(Ref<Layer> layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				m_ImGuiLayer->Begin();
				{
					ANGEL3D_PROFILE_SCOPE("Application::LayerStack::OnImGuiRender");

					for(Ref<Layer> layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(Events::WindowCloseEvent& f_events)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(Events::WindowResizeEvent& f_event)
	{
		ANGEL3D_PROFILE_FUNCTION();

		if(f_event.GetWidth() == 0 || f_event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Angel3D::Renderer::Renderer::OnWindowResize(f_event.GetWidth(), f_event.GetHeight());

		return false;
	}
}