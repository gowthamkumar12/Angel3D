#include "Sandbox3D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox
{
	Sandbox3D::Sandbox3D()
	: Angel3D::Core::Layer("Sandbox3D"),
	  m_CameraController(1920.0f / 1080.0f)
	{
		// Vertex array
		m_vertexArray = Angel3D::Renderer::VertexArray::Create();

		// Vertex buffer
		float vertices[3 * 7] = { 0.0f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
															-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
															0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f };

		Angel3D::Core::Ref<Angel3D::Renderer::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Angel3D::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			Angel3D::Renderer::BufferLayout layout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"},
																								{Angel3D::Renderer::ShaderDataType::Float4, "a_Color"}};

			vertexBuffer->SetLayout(layout);
		}
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		unsigned int indices[3] = {0, 1, 2};

		Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> indexBuffer;
		indexBuffer.reset(Angel3D::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(indexBuffer);

		// Squared Vertex Array
		m_squareVertexArray = Angel3D::Renderer::VertexArray::Create();

		// Square Vertex buffer
		float SquareVertices[4 * 5] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
																			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
																			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
																		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f};

		Angel3D::Core::Ref<Angel3D::Renderer::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Angel3D::Renderer::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		{
			Angel3D::Renderer::BufferLayout SquareLayout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"},
																											{Angel3D::Renderer::ShaderDataType::Float2, "a_TexCoord"}};
			squareVertexBuffer->SetLayout(SquareLayout);
		}
		m_squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		// Squared Index Buffer
		unsigned int squaredIndices[6] = {0, 1, 2, 2, 3, 0};

		Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> squareIndexBuffer;

		squareIndexBuffer.reset(Angel3D::Renderer::IndexBuffer::Create(squaredIndices, sizeof(squaredIndices)  / sizeof(uint32_t)));
		m_squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// Shaders for the triangle
		std::string vertexShader = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjectionMatrix;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color    = a_Color;
					gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
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

		auto triangleShader = m_ShaderLibrary.Load("Triangle", vertexShader, fragmentShader);         // Shader for the Triangle
		auto tileShader     = m_ShaderLibrary.Load("Tiles", "Sandbox/assets/shaders/Tiles.glsl");     // Shader for the Tiles
		auto textureShader  = m_ShaderLibrary.Load("Texture", "Sandbox/assets/shaders/Texture.glsl"); // Shader for the Textures

		m_Texture = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");
		m_Logo    = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/ChernoLogo.png");
	}

	void Sandbox3D::OnUpdate(Angel3D::Core::Timestep f_ts)
	{
		// Update
		m_CameraController.OnUpdate(f_ts);

		// Render
		Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
		Angel3D::Renderer::RenderCommand::Clear();

		Angel3D::Renderer::Renderer::BeginScene(m_CameraController.GetCamera());

		{
			// Tile
			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			for(int y = 0; y < 10; y++)
			{
				for(int x = 0; x < 10; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					m_ShaderLibrary.Get("Tiles")->Bind();
					std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(m_ShaderLibrary.Get("Tiles"))->UploadUniformFloat4("u_Color", m_tileSquareColor);
					Angel3D::Renderer::Renderer::Submit(m_ShaderLibrary.Get("Tiles"), m_squareVertexArray, transform);
				}
			}

			// Big Square with texture
			m_ShaderLibrary.Get("Texture")->Bind();
		  std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);

			m_Texture->Bind();
			Angel3D::Renderer::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_Logo->Bind();
			Angel3D::Renderer::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			// Triangle
			// Angel3D::Renderer::Renderer::Submit(m_ShaderLibrary.Get("Triangle"), m_vertexArray);
		}

		Angel3D::Renderer::Renderer::EndScene();
	}

	void Sandbox3D::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_tileSquareColor));
		ImGui::End();
	}

	void Sandbox3D::OnEvent(Angel3D::Events::Event& f_e)
	{
		m_CameraController.OnEvent(f_e);
	}
} // namespace Sandbox