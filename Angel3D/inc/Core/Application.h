#pragma once

#include "Core/Core.h"
#include "Core/LayerStack.h"
#include "Platform/Windows/Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Angel3D::Core
{
	class Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Angel3D::Events::Event& f_e);

			void PushLayer(Ref<Layer> f_layer);
			void PushOverlay(Ref<Layer> f_overlay);

			inline static Application& Get() { return *m_ApplicationInstance; }

			inline Angel3D::Core::BaseWindow& GetWindow() { return *m_Window; }

		private:
			bool OnWindowClose(Events::WindowCloseEvent& f_event);
			bool OnWindowResize(Events::WindowResizeEvent& f_event);

		private:
			Ref<Angel3D::Core::BaseWindow>      m_Window;
			Ref<Angel3D::ImGuiImpl::ImGuiLayer> m_ImGuiLayer;
			bool                                m_Running = true;
			bool                                m_Minimized = false;
			LayerStack                          m_LayerStack;
			float                               m_LastFrameTime;
			static Application*                 m_ApplicationInstance;
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}