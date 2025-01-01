#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Core/Core.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Angel3D::Renderer
{
  struct Render2DStorage
  {
    Angel3D::Core::Ref<VertexArray> _vertexArray;
    Angel3D::Core::Ref<Shader>      _Shader;
  };

  static Render2DStorage* s_Data;

  void Renderer2D::Init()
  {
    s_Data = new Render2DStorage();

    // Vertex array
		s_Data->_vertexArray = Angel3D::Renderer::VertexArray::Create();

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
		s_Data->_vertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

		Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> indexBuffer;
		indexBuffer = Angel3D::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->_vertexArray->SetIndexBuffer(indexBuffer);

    s_Data->_Shader = Angel3D::Renderer::Shader::Create("Sandbox/assets/shaders/Tiles.glsl");
  }

  void Renderer2D::Shutdown()
  {
    delete s_Data;
  }

  void Renderer2D::BeginScene(const OrthographicCamera &f_camera)
  {
    s_Data->_Shader->Bind();
    s_Data->_Shader->SetMat4("u_ViewProjectionMatrix", f_camera.GetViewProjectionMatrix());
  }

  void Renderer2D::EndScene()
  {
  }

  void Renderer2D::DrawQuad(const glm::vec2 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    DrawQuad({f_position.x, f_position.y, 0.0f}, f_size, f_color);
  }

  void Renderer2D::DrawQuad(const glm::vec3 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    s_Data->_Shader->Bind();
    s_Data->_Shader->SetFloat4("u_Color", f_color);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position) * glm::scale(glm::mat4(1.0f), {f_size.x, f_size.y, 1.0f});
    s_Data->_Shader->SetMat4("u_Transform", transform);

    s_Data->_vertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->_vertexArray);
  }

} // namespace Angel3D::Renderer
