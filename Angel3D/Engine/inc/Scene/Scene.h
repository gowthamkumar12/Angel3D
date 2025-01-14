#pragma once

#include "entt.hpp"
#include "Core/Timestep.h"

namespace Engine::Scene
{
  class Scene
	{
    public:
      Scene();
      ~Scene();

      entt::entity CreateEntity();

      // TEMP
      entt::registry& Reg() { return m_Registry; }

      void OnUpdate(Engine::Core::Timestep ts);

    private:
      entt::registry m_Registry;
	};
} // namespace Engine::Scene