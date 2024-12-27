#include "Sandbox.h"

namespace Sandbox
{
	MainApplicationLayer::MainApplicationLayer()
	: Angel3D::Core::Layer("MainApplicationLayer"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f)
	{
		// Vertex array
		m_vertexArray.reset(Angel3D::Renderer::VertexArray::Create());

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
		m_squareVertexArray.reset(Angel3D::Renderer::VertexArray::Create());

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

		m_Shader = Angel3D::Renderer::Shader::Create(vertexShader, fragmentShader);

		// Shaders for the Tiles
		std::string tile_vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string tile_fragmentShader = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_TileShader = Angel3D::Renderer::Shader::Create(tile_vertexShader, tile_fragmentShader);

		m_TextureShader = Angel3D::Renderer::Shader::Create("Sandbox/assets/shaders/Texture.glsl");

		m_TextureShader->Bind();
		std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(m_TileShader)->UploadUniformInt("u_Texture", 0);

		m_Texture = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");
		m_Logo    = Angel3D::Renderer::Texture2D::Create("Sandbox/assets/textures/ChernoLogo.png");
	}

	void MainApplicationLayer::OnUpdate(Angel3D::Core::Timestep f_ts)
	{
		if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * f_ts;
		}
		else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * f_ts;
		}

		if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * f_ts;
		}
		else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * f_ts;
		}

		if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * f_ts;
		}
		else if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_D))
		{
			m_CameraRotation += m_CameraRotationSpeed * f_ts;
		}

		Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
		Angel3D::Renderer::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Angel3D::Renderer::Renderer::BeginScene(m_Camera);

		{
			// Tile
			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			for(int y = 0; y < 10; y++)
			{
				for(int x = 0; x < 10; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					m_TileShader->Bind();
					std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(m_TileShader)->UploadUniformFloat3("u_Color", m_tileSquareColor);
					Angel3D::Renderer::Renderer::Submit(m_TileShader, m_squareVertexArray, transform);
				}
			}

			// Big Square
			m_Texture->Bind();
			Angel3D::Renderer::Renderer::Submit(m_TextureShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_Logo->Bind();
			Angel3D::Renderer::Renderer::Submit(m_TextureShader, m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			// Triangle
			// Angel3D::Renderer::Renderer::Submit(m_Shader, m_vertexArray);
		}

		Angel3D::Renderer::Renderer::EndScene();
	}

	void MainApplicationLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_tileSquareColor));
		ImGui::End();
	}

	void MainApplicationLayer::OnEvent(Angel3D::Events::Event& f_e)
	{
	}
} // namespace Sandbox

class SandboxApp : public Angel3D::Core::Application
{
	public:
		SandboxApp()
		{
			PushLayer(new Sandbox::MainApplicationLayer());
		}

		~SandboxApp()
		{
		}
};

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
	return new SandboxApp();
}