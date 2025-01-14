#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

namespace Engine::Renderer
{
  class Renderer2D
  {
    public:
      static void Init();
      static void Shutdown();

      static void BeginScene(const OrthographicCamera& f_camera);
      static void EndScene();
      static void Flush();

      // Draw Quad using color
      static void DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size, const glm::vec4& f_color);
      static void DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const glm::vec4& f_color);

      // Draw Quad using Texture
      static void DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size,const Engine::Core::Ref<Texture2D>& f_texture,
                           float f_tilingFactor = 1.0f, const glm::vec4& f_tintColor = glm::vec4(1.0f));
      static void DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const Engine::Core::Ref<Texture2D>& f_texture,
                           float f_tilingFactor = 1.0f, const glm::vec4& f_tintColor = glm::vec4(1.0f));

      static void DrawQuad(const glm::mat4& f_transform, const glm::vec4& f_color);
	  	static void DrawQuad(const glm::mat4& f_transform, const Engine::Core::Ref<Texture2D>& f_texture,
                           float f_tilingFactor = 1.0f, const glm::vec4& f_tintColor = glm::vec4(1.0f));

      // Draw Rotated Quad using Color
      static void DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color);
      static void DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation, const glm::vec4& f_color);

      // Draw Rotated Quad using Texture
      static void DrawRotatedQuad(const glm::vec2& f_position, const glm::vec2& f_size, float f_rotation,
                                  const Engine::Core::Ref<Texture2D>& f_texture, float f_tilingFactor = 1.0f,
                                  const glm::vec4& f_tintColor = glm::vec4(1.0f));
      static void DrawRotatedQuad(const glm::vec3& f_position, const glm::vec2& f_size, float f_rotation,
                                  const Engine::Core::Ref<Texture2D>& f_texture, float f_tilingFactor = 1.0f,
                                  const glm::vec4& f_tintColor = glm::vec4(1.0f));

      // Stats
      struct Statistics
      {
        uint32_t DrawCalls = 0;
        uint32_t QuadCount = 0;
        uint32_t GetTotalVertexCount() { return QuadCount * 4; }
        uint32_t GetTotalIndexCount() { return QuadCount * 6; }
      };

      static void ResetStats();
      static Statistics GetStats();

      private:
        static void FlushAndReset();
  };
} // namespace Engine::Renderer
