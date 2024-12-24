#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace Angel3D::Renderer
{
  class Shader
  {
    public:
      Shader(const std::string& vertexSrc, const std::string& fragSrc);
      ~Shader();

      void Bind() const;
      void Unbind() const;

      void UploadUniformMat4(const std::string& f_name, const glm::mat4& f_matrix);
    private:
      uint32_t m_RendererId;
  };
} // namespace Angel3D::Renderer