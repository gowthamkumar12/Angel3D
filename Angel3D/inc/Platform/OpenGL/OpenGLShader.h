#pragma once

#include "Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Angel3D::Platform::OpenGL
{
  class OpenGLShader : public Angel3D::Renderer::Shader
  {
    public:
      OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc);
      ~OpenGLShader();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      void UploadUniformInt(const std::string& f_name, int f_value);

      void UploadUniformFloat(const std::string& f_name, float f_value);
      void UploadUniformFloat2(const std::string& f_name, const glm::vec2& f_value);
      void UploadUniformFloat3(const std::string& f_name, const glm::vec3& f_value);
      void UploadUniformFloat4(const std::string& f_name, const glm::vec4& f_value);

      void UploadUniformMat3(const std::string& f_name, const glm::mat3& f_matrix);
      void UploadUniformMat4(const std::string& f_name, const glm::mat4& f_matrix);
    private:
      uint32_t m_RendererId;
  };
}