#pragma once

#include "entt.hpp"
#include "Core/Timestep.h"

namespace Engine::Scene
{
  class Entity;

  class Scene
	{
    public:
      Scene();
      ~Scene();

      Entity CreateEntity(const std::string& f_name = std::string());

      void OnUpdate(Engine::Core::Timestep ts);

    private:
      entt::registry m_Registry;

      friend class Entity;
	};
} // namespace Engine::Scene