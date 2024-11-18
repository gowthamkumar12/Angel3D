#pragma once

#include "pch.h"

namespace Angel3D::Renderer
{
  class Shader
  {
    public:
      Shader(const std::string& vertexSrc, const std::string& fragSrc);
      ~Shader();

      void Bind() const;
      void Unbind() const;

    private:
      uint32_t m_RendererId;
  };
} // namespace Angel3D::Renderer