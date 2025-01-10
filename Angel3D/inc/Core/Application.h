#pragma once

#include "Core/Core.h"
#include "Core/LayerStack.h"
#include "Platform/Windows/Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Angel3D::Core
{
	class Application
	{
		public:
			Application();
			virtual ~Application();

			void OnEvent(Angel3D::Events::Event& f_e);

			void PushLayer(Ref<Layer> f_layer);
			void PushOverlay(Ref<Layer> f_overlay);

			inline static Application& Get() { return *m_ApplicationInstance; }

			inline Angel3D::Core::BaseWindow& GetWindow() { return *m_Window; }

			void Close();

		private:
			void Run();
			bool OnWindowClose(Events::WindowCloseEvent& f_event);
			bool OnWindowResize(Events::WindowResizeEvent& f_event);

		private:
			Ref<Angel3D::Core::BaseWindow>      m_Window;
			Ref<Angel3D::ImGuiImpl::ImGuiLayer> m_ImGuiLayer;
			bool                                m_Running = true;
			bool                                m_Minimized = false;
			LayerStack                          m_LayerStack;
			float                               m_LastFrameTime = 0.0f;
			static Application*                 m_ApplicationInstance;

			friend int ::main(int argc, char** argv);
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}