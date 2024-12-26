#pragma once

#include "pch.h"

namespace Angel3D::Renderer
{
  class Shader
  {
    public:
      virtual ~Shader() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      static Shader* Create(const std::string& vertexSrc, const std::string& fragSrc);
  };
} // namespace Angel3D::Renderer