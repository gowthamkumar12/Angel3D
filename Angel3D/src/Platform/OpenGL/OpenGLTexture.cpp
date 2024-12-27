#include "Core/Log.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace Angel3D::Platform::OpenGL
{
  OpenGLTexture2D::OpenGLTexture2D(const std::string& f_filePath)
  : m_FilePath(f_filePath)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(f_filePath.c_str(), &width, &height, &channels, 0);
    ANGEL3D_CORE_ASSERT(data, "Failed to load image!");

    m_Width  = width;
    m_Height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    glDeleteTextures(1, &m_RendererID);
  }

  void OpenGLTexture2D::Bind(uint32_t f_slots) const
  {
    glBindTextureUnit(f_slots, m_RendererID);
  }

} // namespace Angel3D::Platform::OpenGL

