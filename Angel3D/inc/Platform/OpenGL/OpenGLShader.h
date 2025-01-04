#pragma once

#include "Renderer/Shader.h"

#include <glm/glm.hpp>

#include <unordered_map>

namespace Angel3D::Platform::OpenGL
{
  typedef unsigned int GLenum;

  class OpenGLShader : public Angel3D::Renderer::Shader
  {
    public:
      OpenGLShader(const std::string& f_filePath);
      OpenGLShader(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc);
      ~OpenGLShader();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual const std::string& GetName() const override { return m_Name; };

      virtual void SetInt(const std::string& f_name, int f_value) override;
      virtual void SetIntArray(const std::string& f_name, int* f_values, uint32_t f_count) override;
      virtual void SetFloat(const std::string& f_name, float f_value) override;
      virtual void SetFloat3(const std::string& f_name, const glm::vec3& f_value) override;
      virtual void SetFloat4(const std::string& f_name, const glm::vec4& f_value) override;
      virtual void SetMat4(const std::string& f_name, const glm::mat4 f_value) override;

      void UploadUniformInt(const std::string& f_name, int f_value);
      void UploadUniformIntArray(const std::string& f_name, int* f_values, uint32_t f_count);

      void UploadUniformFloat(const std::string& f_name, float f_value);
      void UploadUniformFloat2(const std::string& f_name, const glm::vec2& f_value);
      void UploadUniformFloat3(const std::string& f_name, const glm::vec3& f_value);
      void UploadUniformFloat4(const std::string& f_name, const glm::vec4& f_value);

      void UploadUniformMat3(const std::string& f_name, const glm::mat3& f_matrix);
      void UploadUniformMat4(const std::string& f_name, const glm::mat4& f_matrix);

    private:
      std::string ReadFromFile(const std::string& f_filePath);
      std::unordered_map<GLenum, std::string> PreProcessing(const std::string& f_shaderSource);
      void Compile(const std::unordered_map<GLenum, std::string>& f_shaderSources);

    private:
      uint32_t    m_RendererId;
      std::string m_Name;
  };
}