#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine::Renderer
{
  /**
   * Shader Class
   */
  Engine::Core::Ref<Shader> Shader::Create(const std::string& f_filePath)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Engine::Platform::OpenGL::OpenGLShader>(f_filePath);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  Engine::Core::Ref<Shader> Shader::Create(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::NONE:
        CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
        return nullptr;

      case RendererAPI::API::OPENGL:
        return std::make_shared<Engine::Platform::OpenGL::OpenGLShader>(f_name, vertexSrc, fragSrc);

      default:
        break;
    }

    CORE_ASSERT(false, "Unknown Render API!");
    return nullptr;
  }

  /**
   * ShaderLibrary Class
   */

  void ShaderLibrary::Add(const std::string &f_name, const Engine::Core::Ref<Shader> &f_shader)
  {
    CORE_ASSERT(!Exists(f_name), "Shader already exists!");
    m_Shaders[f_name] = f_shader;
  }

  void ShaderLibrary::Add(const Engine::Core::Ref<Shader> &f_shader)
  {
    auto name = f_shader->GetName();
    Add(name, f_shader);
  }

  Engine::Core::Ref<Shader> ShaderLibrary::Load(const std::string &f_filePath)
  {
    auto shader = Shader::Create(f_filePath);
    Add(shader);
    return shader;
  }

  Engine::Core::Ref<Shader> ShaderLibrary::Load(const std::string &f_name, const std::string &f_filePath)
  {
    auto shader = Shader::Create(f_filePath);
    Add(f_name, shader);
    return shader;
  }

  Engine::Core::Ref<Shader> ShaderLibrary::Load(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc)
  {
    auto shader = Shader::Create(f_name, vertexSrc, fragSrc);
    Add(f_name, shader);
    return shader;
  }

  Engine::Core::Ref<Shader> ShaderLibrary::Get(const std::string &f_name)
  {
    CORE_ASSERT(Exists(f_name), "Shader Not Found!");
    return m_Shaders[f_name];
  }

  bool ShaderLibrary::Exists(const std::string &f_name) const
  {
    return m_Shaders.find(f_name) != m_Shaders.end();
  }
} // namespace Engine::Renderer
