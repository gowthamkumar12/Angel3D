#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

namespace Angel3D::Renderer
{
  class Renderer2D
  {
    public:
      static void Init();
      static void Shutdown();

      static void BeginScene(const OrthographicCamera& f_camera);
      static void EndScene();

      // Primitives
      static void DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size, const glm::vec4& f_color);
      static void DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const glm::vec4& f_color);

      static void DrawQuad(const glm::vec2& f_position, const glm::vec2& f_size, const Angel3D::Core::Ref<Texture2D>& f_texture);
      static void DrawQuad(const glm::vec3& f_position, const glm::vec2& f_size, const Angel3D::Core::Ref<Texture2D>& f_texture);
  };
} // namespace Angel3D::Renderer
