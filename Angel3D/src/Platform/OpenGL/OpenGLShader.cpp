#include "Core/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace Angel3D::Platform::OpenGL
{
  static GLenum ShaderTypeFromString(const std::string& f_type)
  {
    if(f_type == "vertex")
    {
      return GL_VERTEX_SHADER;
    }
    if(f_type == "fragment" || f_type == "pixel")
    {
      return GL_FRAGMENT_SHADER;
    }

    ANGEL3D_CORE_ASSERT(false, "Invalid shader type!");
    return 0;
  }

  OpenGLShader::OpenGLShader(const std::string& f_filePath)
  {
    std::string source = ReadFromFile(f_filePath);
    auto shaderSources = PreProcessing(source);
    Compile(shaderSources);

    // Extract name from the file path
    auto lastSlash = f_filePath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = f_filePath.rfind('.');
    auto count = lastDot == std::string::npos ? f_filePath.size() - lastSlash : lastDot - lastSlash;
    m_Name = f_filePath.substr(lastSlash, count);
  }

  OpenGLShader::OpenGLShader(const std::string& f_name, const std::string &vertexSrc, const std::string &fragSrc)
  : m_Name(f_name)
  {
    std::unordered_map<GLenum, std::string> shaderSource;
    shaderSource[GL_VERTEX_SHADER] = vertexSrc;
    shaderSource[GL_FRAGMENT_SHADER] = fragSrc;
    Compile(shaderSource);
  }

  OpenGLShader::~OpenGLShader()
  {
    glDeleteProgram(m_RendererId);
  }

  std::string OpenGLShader::ReadFromFile(const std::string& f_filePath)
  {
    std::string result;
    std::ifstream in(f_filePath, std::ios::in | std::ios::binary);
    if(in)
    {
      in.seekg(0, std::ios::end);
      result.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
      in.close();
    }
    else
    {
      ANGEL3D_CORE_ERROR("Could not load the shader file '{0}'", f_filePath);
    }

    return result;
  }

  std::unordered_map<GLenum, std::string> OpenGLShader::PreProcessing(const std::string& f_shaderSource)
  {
    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken  = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos             = f_shaderSource.find(typeToken, 0);
    while (pos != std::string::npos)
    {
      size_t eol = f_shaderSource.find_first_of("\r\n", pos);
      ANGEL3D_CORE_ASSERT(eol != std::string::npos, "Syntax error!");

      size_t begin = pos + typeTokenLength + 1;
      std::string type = f_shaderSource.substr(begin, eol - begin);
      ANGEL3D_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification");

      size_t nextLinePos = f_shaderSource.find_first_not_of("\r\n", eol);
      pos = f_shaderSource.find(typeToken, nextLinePos);
      shaderSources[ShaderTypeFromString(type)] = f_shaderSource.substr(nextLinePos,
                                                                        pos - (nextLinePos == std::string::npos ? f_shaderSource.size() - 1 : nextLinePos));
    }

    return shaderSources;
  }

  void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& f_shaderSources)
  {
    GLuint program = glCreateProgram();
    ANGEL3D_CORE_ASSERT(f_shaderSources.size() <= 2, "We only support 2 shaders for now.")
    std::array<GLenum, 2> glShaderIDs;
    int glShaderIndex = 0;

    for (auto& ele : f_shaderSources)
    {
      GLenum type = ele.first;
      const std::string source = ele.second;

      // Create an empty shader handle
      GLuint shader = glCreateShader(type);

      // Send the vertex shader source code to GL
      // Note that std::string's .c_str is NULL character terminated.
      const GLchar* sourceCSTR = source.c_str();
      glShaderSource(shader, 1, &sourceCSTR, 0);

      // Compile the vertex shader
      glCompileShader(shader);

      GLint isCompiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
      if(isCompiled == GL_FALSE)
      {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(shader);

        ANGEL3D_CORE_ERROR("{0}", infoLog.data());
        ANGEL3D_CORE_ASSERT(false, "Shader compilation failure!");
        break;
      }

      glAttachShader(program, shader);
      glShaderIDs[glShaderIndex++] = shader;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    m_RendererId = program;

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      glDeleteProgram(program);

      // Don't leak shaders either.
      for(auto id : glShaderIDs)
      {
        glDeleteShader(id);
      }

      ANGEL3D_CORE_ERROR("{0}", infoLog.data());
      ANGEL3D_CORE_ASSERT(false, "Shader linking failure!");
      return;
    }

    // Always detach shaders after a successful link.
    for(auto id : glShaderIDs)
    {
      glDetachShader(program, id);
    }
  }

  void OpenGLShader::Bind() const
  {
    glUseProgram(m_RendererId);
  }

  void OpenGLShader::Unbind() const
  {
    glUseProgram(0);
  }

  void OpenGL::OpenGLShader::UploadUniformInt(const std::string &f_name, int f_value)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniform1i(location, f_value);
  }

  void OpenGL::OpenGLShader::UploadUniformFloat(const std::string &f_name, float f_value)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniform1f(location, f_value);
  }

  void OpenGL::OpenGLShader::UploadUniformFloat2(const std::string &f_name, const glm::vec2 &f_value)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniform2f(location, f_value.x, f_value.y);
  }

  void OpenGL::OpenGLShader::UploadUniformFloat3(const std::string &f_name, const glm::vec3 &f_value)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniform3f(location, f_value.x, f_value.y, f_value.z);
  }

  void OpenGL::OpenGLShader::UploadUniformFloat4(const std::string &f_name, const glm::vec4 &f_value)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniform4f(location, f_value.x, f_value.y, f_value.z, f_value.w);
  }

  void OpenGL::OpenGLShader::UploadUniformMat3(const std::string &f_name, const glm::mat3 &f_matrix)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(f_matrix));
  }

  void OpenGLShader::UploadUniformMat4(const std::string &f_name, const glm::mat4 &f_matrix)
  {
    GLint location = glGetUniformLocation(m_RendererId, f_name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(f_matrix));
  }

} // namespace Angel3D::Platform::OpenGL