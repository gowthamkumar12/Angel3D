#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Core/Core.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine::Renderer
{
  struct QuadVertex
  {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float     TexIndex;
		float     TilingFactor;
  };

  struct Renderer2DData
  {
    static const uint32_t MaxQuads        = 20000;
		static const uint32_t MaxVertices     = MaxQuads * 4;
		static const uint32_t MaxIndices      = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

    Engine::Core::Ref<VertexArray>  QuadVertexArray;
    Engine::Core::Ref<VertexBuffer> QuadVertexBuffer;
    Engine::Core::Ref<Shader>       TextureShader;
    Engine::Core::Ref<Texture2D>    WhiteTexture;

    uint32_t    QuadIndexCount       = 0;
    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr  = nullptr;

    std::array<Engine::Core::Ref<Texture2D>,
                                  MaxTextureSlots> TextureSlots;
		uint32_t                                       TextureSlotIndex = 1; // 0 = white texture

    glm::vec4 QuadVertexPositions[4];

    Renderer2D::Statistics m_stats;
  };

  static Renderer2DData s_Data;

  void Renderer2D::Init()
  {
    PROFILE_FUNCTION();

    // Creating a vertex array(i.e., Array that contains all the vertices to draw a quad)
		s_Data.QuadVertexArray = Engine::Renderer::VertexArray::Create();

    // Creating a vertex buffer that holds the n number of vertex arrays(Max 10000 in this case)
		s_Data.QuadVertexBuffer = Engine::Renderer::VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		{
			Engine::Renderer::BufferLayout layout = {{Engine::Renderer::ShaderDataType::Float3, "a_Position"},
                                                {Engine::Renderer::ShaderDataType::Float4, "a_Color"},
                                                {Engine::Renderer::ShaderDataType::Float2, "a_TexCoord"},
                                                {Engine::Renderer::ShaderDataType::Float,  "a_TexIndex"},
			                                          {Engine::Renderer::ShaderDataType::Float,  "a_TilingFactor"}};

			s_Data.QuadVertexBuffer->SetLayout(layout);
		}
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

    // Creating an index buffer for each vertex
    uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

    Engine::Core::Ref<Engine::Renderer::IndexBuffer> quadIndexBuffer;
		quadIndexBuffer = Engine::Renderer::IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    delete[] quadIndices;

    s_Data.WhiteTexture = Engine::Renderer::Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
    {
			samplers[i] = i;
    }

    s_Data.TextureShader = Engine::Renderer::Shader::Create("Assets/shaders/Texture.glsl");
    s_Data.TextureShader->Bind();

    s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

    // Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
  }

  void Renderer2D::Shutdown()
  {
    PROFILE_FUNCTION();

    delete[] s_Data.QuadVertexBufferBase;
  }

  void Renderer2D::BeginScene(const OrthographicCamera &f_camera)
  {
    PROFILE_FUNCTION();

    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetMat4("u_ViewProjectionMatrix", f_camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
  }

  void Renderer2D::EndScene()
  {
    PROFILE_FUNCTION();

    uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    Flush();
  }

  void Renderer2D::Flush()
  {
    if (s_Data.QuadIndexCount == 0)
    {
			return;
    }

    // Bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
    {
			s_Data.TextureSlots[i]->Bind(i);
    }

    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

    s_Data.m_stats.DrawCalls++;
  }

  void Renderer2D::FlushAndReset()
  {
    EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
  }

  void Renderer2D::DrawQuad(const glm::vec2 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    DrawQuad({f_position.x, f_position.y, 0.0f}, f_size, f_color);
  }

  void Renderer2D::DrawQuad(const glm::vec3 &f_position, const glm::vec2 &f_size, const glm::vec4 &f_color)
  {
    PROFILE_FUNCTION();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
		                   	* glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

		DrawQuad(transform, f_color);
  }

  void Renderer2D::DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size,const Engine::Core::Ref<Texture2D>& f_texture,
                           float f_tilingFactor, const glm::vec4& f_tintColor)
  {
    DrawQuad({f_position.x, f_position.y, 0.0f}, f_size, f_texture, f_tilingFactor, f_tintColor);
  }

  void Renderer2D::DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const Engine::Core::Ref<Texture2D>& f_texture,
                            float f_tilingFactor, const glm::vec4& f_tintColor)
  {
    PROFILE_FUNCTION();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
			                  * glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

		DrawQuad(transform, f_texture, f_tilingFactor);
  }

  void Renderer2D::DrawQuad(const glm::mat4& f_transform, const glm::vec4& f_color)
  {
    PROFILE_FUNCTION();

    constexpr size_t    quadVertexCount = 4;
		const float         textureIndex    = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float         tilingFactor    = 1.0f;

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
    {
			FlushAndReset();
    }

    for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position     = f_transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color        = f_color;
			s_Data.QuadVertexBufferPtr->TexCoord     = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.m_stats.QuadCount++;
  }

  void Renderer2D::DrawQuad(const glm::mat4& f_transform, const Engine::Core::Ref<Texture2D>& f_texture,
                            float f_tilingFactor, const glm::vec4& f_tintColor)
	{
		PROFILE_FUNCTION();

		constexpr size_t    quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
    {
			FlushAndReset();
    }

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *f_texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = f_texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position     = f_transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color        = f_tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord     = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = f_tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.m_stats.QuadCount++;
	}

  void Renderer2D::DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color)
	{
		DrawRotatedQuad({ f_position.x, f_position.y, 0.0f }, f_size, f_rotation, f_color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color)
	{
    PROFILE_FUNCTION();

    constexpr size_t    quadVertexCount = 4;
		const float         textureIndex    = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float         tilingFactor    = 1.0f;

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
    {
			FlushAndReset();
    }

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
                        * glm::rotate(glm::mat4(1.0f), glm::radians(f_rotation), { 0.0f, 0.0f, 1.0f })
			                  * glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

    for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position     = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color        = f_color;
			s_Data.QuadVertexBufferPtr->TexCoord     = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

    s_Data.m_stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation,
                                   const Engine::Core::Ref<Texture2D>& f_texture, float f_tilingFactor,
                                   const glm::vec4& f_tintColor)
	{
		DrawRotatedQuad({ f_position.x, f_position.y, 0.0f }, f_size, f_rotation, f_texture, f_tilingFactor, f_tintColor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation,
                                   const Engine::Core::Ref<Texture2D>& f_texture, float f_tilingFactor,
                                   const glm::vec4& f_tintColor)
	{
    PROFILE_FUNCTION();

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
    {
			FlushAndReset();
    }

		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *f_texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
      if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
      {
				FlushAndReset();
      }

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = f_texture;
			s_Data.TextureSlotIndex++;
		}

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), f_position)
                        * glm::rotate(glm::mat4(1.0f), glm::radians(f_rotation), { 0.0f, 0.0f, 1.0f })
                        * glm::scale(glm::mat4(1.0f), { f_size.x, f_size.y, 1.0f });

    s_Data.QuadVertexBufferPtr->Position     = transform * s_Data.QuadVertexPositions[0];
    s_Data.QuadVertexBufferPtr->Color        = f_tintColor;
    s_Data.QuadVertexBufferPtr->TexCoord     = { 0.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = f_tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position     = transform * s_Data.QuadVertexPositions[1];
    s_Data.QuadVertexBufferPtr->Color        = f_tintColor;
    s_Data.QuadVertexBufferPtr->TexCoord     = { 1.0f, 0.0f };
    s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = f_tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position     = transform * s_Data.QuadVertexPositions[2];
    s_Data.QuadVertexBufferPtr->Color        = f_tintColor;
    s_Data.QuadVertexBufferPtr->TexCoord     = { 1.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = f_tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadVertexBufferPtr->Position     = transform * s_Data.QuadVertexPositions[3];
    s_Data.QuadVertexBufferPtr->Color        = f_tintColor;
    s_Data.QuadVertexBufferPtr->TexCoord     = { 0.0f, 1.0f };
    s_Data.QuadVertexBufferPtr->TexIndex     = textureIndex;
    s_Data.QuadVertexBufferPtr->TilingFactor = f_tilingFactor;
    s_Data.QuadVertexBufferPtr++;

    s_Data.QuadIndexCount += 6;

    s_Data.m_stats.QuadCount++;
  }

  void Renderer2D::ResetStats()
	{
		memset(&s_Data.m_stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.m_stats;
	}

} // namespace Engine::Renderer
