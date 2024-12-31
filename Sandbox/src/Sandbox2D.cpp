#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox
{
  Sandbox2D::Sandbox2D()
  : Angel3D::Core::Layer("Sandbox3D"),
	  m_CameraController(1920.0f / 1080.0f)
  {}

  void Sandbox2D::OnAttach()
  {
    // Vertex array
		m_vertexArray = Angel3D::Renderer::VertexArray::Create();

		// Vertex buffer
		float vertices[4 * 3] = { -0.5f, -0.5f, 0.0f,
															 0.5f, -0.5f, 0.0f,
															 0.5f,  0.5f, 0.0f,
															-0.5f,  0.5f, 0.0f};

		Angel3D::Core::Ref<Angel3D::Renderer::VertexBuffer> vertexBuffer;
		vertexBuffer = Angel3D::Renderer::VertexBuffer::Create(vertices, sizeof(vertices));
		{
			Angel3D::Renderer::BufferLayout layout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"}};

			vertexBuffer->SetLayout(layout);
		}
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

		Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> indexBuffer;
		indexBuffer = Angel3D::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_vertexArray->SetIndexBuffer(indexBuffer);

    m_Shader = Angel3D::Renderer::Shader::Create("Sandbox/assets/shaders/Tiles.glsl");
  }

  void Sandbox2D::OnDetach()
  {
  }

  void Sandbox2D::OnUpdate(Angel3D::Core::Timestep f_ts)
  {
    // Update
		m_CameraController.OnUpdate(f_ts);

		// Render
		Angel3D::Renderer::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
		Angel3D::Renderer::RenderCommand::Clear();

		Angel3D::Renderer::Renderer::BeginScene(m_CameraController.GetCamera());

    m_Shader->Bind();
    std::dynamic_pointer_cast<Angel3D::Platform::OpenGL::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_tileSquareColor);
    Angel3D::Renderer::Renderer::Submit(m_Shader, m_vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Angel3D::Renderer::Renderer::EndScene();
  }

  void Sandbox2D::OnImGuiRender()
  {
    ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_tileSquareColor));
		ImGui::End();
  }

  void Sandbox2D::OnEvent(Angel3D::Events::Event &f_e)
  {
    m_CameraController.OnEvent(f_e);
  }
} // namespace Sandbox
