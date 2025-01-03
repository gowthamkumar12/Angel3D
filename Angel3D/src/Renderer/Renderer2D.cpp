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
    Angel3D::Core::Ref<Shader>      _TextureShader;
    Angel3D::Core::Ref<Texture2D>   _WhiteTexture;
  };

  static Render2DStorage* s_Data;

  void Renderer2D::Init()
  {
    ANGEL3D_PROFILE_FUNCTION();

    s_Data = new Render2DStorage();

    // Vertex array
		s_Data->_vertexArray = Angel3D::Renderer::VertexArray::Create();

		// Vertex buffer
		float vertices[4 * 5] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
															 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
															 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
															-0.5f,  0.5f, 0.0f, 0.0f, 1.0f};

		Angel3D::Core::Ref<Angel3D::Renderer::VertexBuffer> vertexBuffer;
		vertexBuffer = Angel3D::Renderer::VertexBuffer::Create(vertices, sizeof(vertices));
		{
			Angel3D::Renderer::BufferLayout layout = {{Angel3D::Renderer::ShaderDataType::Float3, "a_Position"},
                                                {Angel3D::Renderer::ShaderDataType::Float2, "a_TexCoord"}};

			vertexBuffer->SetLayout(layout);
		}
		s_Data->_vertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

		Angel3D::Core::Ref<Angel3D::Renderer::IndexBuffer> indexBuffer;
		indexBuffer = Angel3D::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->_vertexArray->SetIndexBuffer(indexBuffer);

    s_Data->_WhiteTexture = Angel3D::Renderer::Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data->_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    s_Data->_TextureShader = Angel3D::Renderer::Shader::Create("Sandbox/assets/shaders/Texture.glsl");
    s_Data->_TextureShader->Bind();
    s_Data->_TextureShader->SetInt("u_Texture", 0);
  }

  void Renderer2D::Shutdown()
  {
    ANGEL3D_PROFILE_FUNCTION();

    delete s_Data;
  }

  void Renderer2D::BeginScene(const OrthographicCamera &f_camera)
  {
    ANGEL3D_PROFILE_FUNCTION();

    s_Data->_TextureShader->Bind();
    s_Data->_TextureShader->SetMat4("u_ViewProjectionMatrix", f_camera.GetViewProjectionMatrix());
  }

  void Renderer2D::EndScene()
  {
    ANGEL3D_PROFILE_FUNCTION();
  }

  void Renderer2D::DrawQuad(const glm::vec2 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    DrawQuad({f_position.x, f_position.y, 0.0f}, f_size, f_color);
  }

  void Renderer2D::DrawQuad(const glm::vec3 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    ANGEL3D_PROFILE_FUNCTION();

    s_Data->_TextureShader->SetFloat4("u_Color", f_color);
    s_Data->_TextureShader->SetFloat("u_TilingFactor", 1.0f);

    s_Data->_WhiteTexture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position) * glm::scale(glm::mat4(1.0f), {f_size.x, f_size.y, 1.0f});
    s_Data->_TextureShader->SetMat4("u_Transform", transform);

    s_Data->_vertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->_vertexArray);
  }

  void Renderer2D::DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size,const Angel3D::Core::Ref<Texture2D>& f_texture,
                           float f_tilingFactor, const glm::vec4& f_tintColor)
  {
    DrawQuad({f_position.x, f_position.y, 0.0f}, f_size, f_texture, f_tilingFactor, f_tintColor);
  }

  void Renderer2D::DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const Angel3D::Core::Ref<Texture2D>& f_texture,
                            float f_tilingFactor, const glm::vec4& f_tintColor)
  {
    ANGEL3D_PROFILE_FUNCTION();

    s_Data->_TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
    s_Data->_TextureShader->SetFloat("u_TilingFactor", f_tilingFactor);
    f_texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position) * glm::scale(glm::mat4(1.0f), {f_size.x, f_size.y, 1.0f});
    s_Data->_TextureShader->SetMat4("u_Transform", transform);

    s_Data->_vertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->_vertexArray);
  }

  void Renderer2D::DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color)
	{
		DrawRotatedQuad({ f_position.x, f_position.y, 0.0f }, f_size, f_rotation, f_color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color)
	{
		ANGEL3D_PROFILE_FUNCTION();

		s_Data->_TextureShader->SetFloat4("u_Color", f_color);
		s_Data->_TextureShader->SetFloat("u_TilingFactor", 1.0f);

		s_Data->_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
			* glm::rotate(glm::mat4(1.0f), f_rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

		s_Data->_TextureShader->SetMat4("u_Transform", transform);
		s_Data->_vertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->_vertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation,
                                  const Angel3D::Core::Ref<Texture2D>& f_texture, float f_tilingFactor,
                                  const glm::vec4& f_tintColor)
	{
		DrawRotatedQuad({ f_position.x, f_position.y, 0.0f }, f_size, f_rotation, f_texture, f_tilingFactor, f_tintColor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation,
                                  const Angel3D::Core::Ref<Texture2D>& f_texture, float f_tilingFactor,
                                  const glm::vec4& f_tintColor)
	{
		ANGEL3D_PROFILE_FUNCTION();

		s_Data->_TextureShader->SetFloat4("u_Color", f_tintColor);
		s_Data->_TextureShader->SetFloat("u_TilingFactor", f_tilingFactor);

		f_texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
			* glm::rotate(glm::mat4(1.0f), f_rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

		s_Data->_TextureShader->SetMat4("u_Transform", transform);
		s_Data->_vertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->_vertexArray);
  }

} // namespace Angel3D::Renderer
