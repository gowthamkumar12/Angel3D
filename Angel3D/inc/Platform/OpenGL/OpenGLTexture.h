#pragma once

#include "Renderer/Texture.h"

namespace Angel3D::Platform::OpenGL
{
  class OpenGLTexture2D : public Angel3D::Renderer::Texture2D
  {
    public:
      OpenGLTexture2D(const std::string& f_filePath);
      virtual ~OpenGLTexture2D();

      virtual uint32_t GetWidth() const override { return m_Width; }
      virtual uint32_t GetHeight() const override { return m_Height; }

      virtual void Bind(uint32_t f_slot = 0) const override;

    private:
      std::string m_FilePath;
      uint32_t    m_Width, m_Height;
      uint32_t    m_RendererID;
  };
} // namespace Angel3D::Platform::OpenGL
