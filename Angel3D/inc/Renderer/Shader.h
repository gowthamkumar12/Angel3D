#pragma once

#include "pch.h"
#include "Core/Core.h"

namespace Angel3D::Renderer
{
  class Shader
  {
    public:
      virtual ~Shader() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      static Angel3D::Core::Ref<Shader> Create(const std::string& f_filePath);
      static Angel3D::Core::Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragSrc);
  };
} // namespace Angel3D::Renderer