#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Angel3D::Renderer
{
  /**
   * Shader Class
   */
  Angel3D::Core::Ref<Shader> Shader::Create(const std::string& f_filePath)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Angel3D::Platform::OpenGL::OpenGLShader>(f_filePath);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Angel3D::Core::Ref<Shader> Shader::Create(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        ANGEL3D_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Angel3D::Platform::OpenGL::OpenGLShader>(f_name, vertexSrc, fragSrc);

      default:
        break;
    }

    ANGEL3D_CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  /**
   * ShaderLibrary Class
   */

  void ShaderLibrary::Add(const std::string &f_name, const Angel3D::Core::Ref<Shader> &f_shader)
  {
    ANGEL3D_CORE_ASSERT(!Exists(f_name), "Shader already exists!");
    m_Shaders[f_name] = f_shader;
  }

  void ShaderLibrary::Add(const Angel3D::Core::Ref<Shader> &f_shader)
  {
    auto name = f_shader->GetName();
    Add(name, f_shader);
  }

  Angel3D::Core::Ref<Shader> ShaderLibrary::Load(const std::string &f_filePath)
  {
    auto shader = Shader::Create(f_filePath);
    Add(shader);
    return shader;
  }

  Angel3D::Core::Ref<Shader> ShaderLibrary::Load(const std::string &f_name, const std::string &f_filePath)
  {
    auto shader = Shader::Create(f_filePath);
    Add(f_name, shader);
    return shader;
  }

  Angel3D::Core::Ref<Shader> ShaderLibrary::Load(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc)
  {
    auto shader = Shader::Create(f_name, vertexSrc, fragSrc);
    Add(f_name, shader);
    return shader;
  }

  Angel3D::Core::Ref<Shader> ShaderLibrary::Get(const std::string &f_name)
  {
    ANGEL3D_CORE_ASSERT(Exists(f_name), "Shader Not Found!");
    return m_Shaders[f_name];
  }

  bool ShaderLibrary::Exists(const std::string &f_name) const
  {
    return m_Shaders.find(f_name) != m_Shaders.end();
  }
} // namespace Angel3D::Renderer
