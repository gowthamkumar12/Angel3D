#pragma once

#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace Angel3D::Platform::OpenGL
{
  class OpenGLTexture2D : public Angel3D::Renderer::Texture2D
  {
    public:
      OpenGLTexture2D(uint32_t f_width, uint32_t f_height);
      OpenGLTexture2D(const std::string& f_filePath);
      virtual ~OpenGLTexture2D();

      virtual uint32_t GetWidth() const override { return m_Width; }
      virtual uint32_t GetHeight() const override { return m_Height; }
      virtual uint32_t GetRendererID() const override { return m_RendererID; }

      virtual void SetData(void* data, uint32_t size) override;

      virtual void Bind(uint32_t f_slot = 0) const override;

      virtual bool operator==(const Angel3D::Renderer::Texture& f_other) const override
      {
        return m_RendererID == ((OpenGLTexture2D&)f_other).m_RendererID;
      }

    private:
      std::string m_FilePath;
      uint32_t    m_Width, m_Height;
      uint32_t    m_RendererID;
      GLenum      m_InternalFormat, m_DataFormat;
  };
} // namespace Angel3D::Platform::OpenGL
