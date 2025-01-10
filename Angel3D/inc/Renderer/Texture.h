#pragma once

#include "Core/Core.h"

namespace Angel3D::Renderer
{
  class Texture
  {
    public:
      virtual ~Texture() = default;

      virtual uint32_t GetWidth() const = 0;
      virtual uint32_t GetHeight() const = 0;
      virtual uint32_t GetRendererID() const = 0;

      virtual void SetData(void* data, uint32_t size) = 0;

      virtual void Bind(uint32_t f_slot = 0) const = 0;

      virtual bool operator==(const Texture& f_other) const = 0;
  };

  class Texture2D : public Texture
  {
    public:
      virtual ~Texture2D() = default;

      static Angel3D::Core::Ref<Texture2D> Create(uint32_t f_width, uint32_t f_height);
      static Angel3D::Core::Ref<Texture2D> Create(const std::string& f_filePath);
  };
} // namespace Angel3D::Renderer