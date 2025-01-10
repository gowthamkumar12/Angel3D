#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Timestep.h"
#include "Events/ApplicationEvent.h"
#include "Platform/Windows/Input.h"
#include "Renderer/Renderer.h"

namespace Engine::Core
{
	Application* Application::m_ApplicationInstance = nullptr;

	Application::Application(const std::string& f_name)
	{
		PROFILE_FUNCTION();

		CORE_ASSERT(!m_ApplicationInstance, "Core application already exists.");
		m_ApplicationInstance = this;

		m_Window = Engine::Core::BaseWindow::Create(Engine::Core::WindowProps(f_name));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Engine::Renderer::Renderer::Init();

		// Creating a new ImGui Layer and pushing it to the layer stack as a overlay.
		m_ImGuiLayer = CreateRef<Engine::ImGuiImpl::ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		PROFILE_FUNCTION();

		Engine::Renderer::Renderer::Shutdown();
	}

	void Application::PushLayer(Ref<Layer> f_layer)
	{
		PROFILE_FUNCTION();

		m_LayerStack.PushLayer(f_layer);
		f_layer->OnAttach();
	}

	void Application::PushOverlay(Ref<Layer> f_overlay)
	{
		PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(f_overlay);
		f_overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Engine::Events::Event& f_e)
	{
		PROFILE_FUNCTION();

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
		PROFILE_FUNCTION();

		while (m_Running)
		{
			PROFILE_SCOPE("Application::RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if(!m_Minimized)
			{
				{
					PROFILE_SCOPE("Application::LayerStack::OnUpdate");

					for(Ref<Layer> layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				m_ImGuiLayer->Begin();
				{
					PROFILE_SCOPE("Application::LayerStack::OnImGuiRender");

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
		PROFILE_FUNCTION();

		if(f_event.GetWidth() == 0 || f_event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Engine::Renderer::Renderer::OnWindowResize(f_event.GetWidth(), f_event.GetHeight());

		return false;
	}
}