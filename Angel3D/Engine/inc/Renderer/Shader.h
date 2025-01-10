#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>
#include <unordered_map>

namespace Engine::Renderer
{
  class Shader
  {
    public:
      virtual ~Shader() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void SetInt(const std::string& f_name, int f_value) = 0;
      virtual void SetIntArray(const std::string& f_name, int* f_values, uint32_t f_count) = 0;
      virtual void SetFloat(const std::string& f_name, float f_value) = 0;
      virtual void SetFloat3(const std::string& f_name, const glm::vec3& f_value) = 0;
      virtual void SetFloat4(const std::string& f_name, const glm::vec4& f_value) = 0;
      virtual void SetMat4(const std::string& f_name, const glm::mat4 f_value) = 0;

      virtual const std::string& GetName() const = 0;

      static Engine::Core::Ref<Shader> Create(const std::string& f_filePath);
      static Engine::Core::Ref<Shader> Create(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc);
  };

  class ShaderLibrary
  {
    public:
      void Add(const std::string& f_name,const Engine::Core::Ref<Shader>& f_shader);
      void Add(const Engine::Core::Ref<Shader>& f_shader);

      Engine::Core::Ref<Shader> Load(const std::string& f_filePath);
      Engine::Core::Ref<Shader> Load(const std::string& f_name, const std::string& f_filePath);
      Engine::Core::Ref<Shader> Load(const std::string& f_name, const std::string& vertexSrc, const std::string& fragSrc);

      Engine::Core::Ref<Shader> Get(const std::string& f_name);

      bool Exists(const std::string& f_name) const;
    private:
      std::unordered_map<std::string, Engine::Core::Ref<Shader>> m_Shaders;
  };
} // namespace Engine::Renderer