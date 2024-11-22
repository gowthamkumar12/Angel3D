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

		// Vertex array
		m_vertexArray.reset(Angel3D::Renderer::VertexArray::Create());

		// Vertex buffer
		float vertices[3 * 7] = {  0.0f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		                          -0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
															 0.5f,  -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f };

		std::shared_ptr<Angel3D::Renderer::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Angel3D::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			Angel3D::Renderer::BufferLayout layout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"},
																								{Angel3D::Renderer::ShaderDataType::Float4, "a_Color"}};

			vertexBuffer->SetLayout(layout);
		}
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		unsigned int indices[3] = {0, 1, 2};

		std::shared_ptr<Angel3D::Renderer::IndexBuffer> indexBuffer;
		indexBuffer.reset(Angel3D::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(indexBuffer);

		// Squared Vertex Array
		m_squareVertexArray.reset(Angel3D::Renderer::VertexArray::Create());

		// Square Vertex buffer
		float SquareVertices[4 * 7] = { -0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		                                 0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
																		 0.75f,  0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
																	  -0.75f,  0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, };

		std::shared_ptr<Angel3D::Renderer::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Angel3D::Renderer::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		{
			Angel3D::Renderer::BufferLayout SquareLayout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"},
			                                          {Angel3D::Renderer::ShaderDataType::Float4, "a_Color"}};
			squareVertexBuffer->SetLayout(SquareLayout);
		}
		m_squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		// Squared Index Buffer
		unsigned int squaredIndices[6] = {0, 1, 2, 2, 3, 0};

		std::shared_ptr<Angel3D::Renderer::IndexBuffer> squareIndexBuffer;

		squareIndexBuffer.reset(Angel3D::Renderer::IndexBuffer::Create(squaredIndices, sizeof(squaredIndices)  / sizeof(uint32_t)));
		m_squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexShader = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
				  v_Position = a_Position;
					v_Color    = a_Color;
					gl_Position = vec4(a_Position, 1.0);
				}
			)";

			std::string fragmentShader = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5, 1.0);
					color = vec4(v_Color);
				}
			)";

		m_Shader.reset(new Angel3D::Renderer::Shader(vertexShader, fragmentShader));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			m_squareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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