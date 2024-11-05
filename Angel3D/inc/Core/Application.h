#pragma once

#include "Core.h"
#include "Platform/Windows/Window.h"

#include "Events/ApplicationEvent.h"
#include "Core/LayerStack.h"

namespace Angel3D
{
	namespace Core
	{
		class ANGEL3D_API Application
		{
			public:
				Application();
				~Application();

				void Run();

				void OnEvent(Angel3D::Events::Event& f_e);

				void PushLayer(Layer* f_layer);
				void PushOverlay(Layer* f_overlay);

				inline static Application& Get() { return *m_ApplicationInstance; }

				inline Angel3D::Core::BaseWindow& GetWindow() { return *m_Window; }

			private:
			  bool OnWindowClose(Events::WindowCloseEvent& f_event);

				std::unique_ptr<Angel3D::Core::BaseWindow> m_Window;
				bool m_Running = true;

				LayerStack m_LayerStack;

				static Application* m_ApplicationInstance;
			};

			// To be defined in the CLIENT
			Application* CreateApplication();
	}
}