#include <Renderer/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Angel3D::Renderer
{
  OrthographicCamera::OrthographicCamera(float f_left, float f_right,
                                         float f_bottom, float f_top)
  : m_ProjectionMatrix(glm::ortho(f_left, f_right, f_bottom, f_top, -1.0f, 1.0f)),
    m_ViewMatrix(1.0f)
  {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }

  void OrthographicCamera::SetProjectioMatrix(float f_left, float f_right,
                                              float f_bottom, float f_top)
  {
    m_ProjectionMatrix = glm::ortho(f_left, f_right, f_bottom, f_top, -1.0f, 1.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }

  void OrthographicCamera::RecalculateViewMatrix()
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }
}

