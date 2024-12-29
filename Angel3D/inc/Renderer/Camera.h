#pragma once

#include <glm/glm.hpp>

namespace Angel3D::Renderer
{
  class OrthographicCamera
  {
    public:
      OrthographicCamera(float f_left, float f_right, float f_bottom, float f_top);

      void SetProjectioMatrix(float f_left, float f_right, float f_bottom, float f_top);

      const glm::vec3& GetPosition() const { return m_Position; }
      void SetPosition(const glm::vec3& f_position)
      {
        m_Position = f_position;
        RecalculateViewMatrix();
      }

      float GetRotation() const { return m_Rotation; }
      void SetRotation(float f_rotation)
      {
        m_Rotation = f_rotation;
        RecalculateViewMatrix();
      }

      const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
      const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
      const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
      void RecalculateViewMatrix();
    private:
      glm::mat4 m_ProjectionMatrix;
      glm::mat4 m_ViewMatrix;
      glm::mat4 m_ViewProjectionMatrix;

      glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
      float     m_Rotation = 0.0f;
 };
} // namespace Angel3D::Renderer
