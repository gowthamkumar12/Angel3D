#pragma once

#include "Core/Core.h"
#include "Core/LayerStack.h"
#include "Platform/Windows/Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Angel3D::Core
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
			Angel3D::ImGuiImpl::ImGuiLayer* m_ImGuiLayer;
			bool m_Running = true;
			LayerStack m_LayerStack;

			std::shared_ptr<Angel3D::Renderer::VertexArray>  m_vertexArray;
			std::shared_ptr<Angel3D::Renderer::VertexArray>  m_squareVertexArray;
			std::shared_ptr<Angel3D::Renderer::Shader>       m_Shader;

			static Application* m_ApplicationInstance;
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}