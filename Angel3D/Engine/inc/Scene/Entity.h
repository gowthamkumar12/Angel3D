#pragma once

#include "Scene/Scene.h"

namespace Engine::Scene
{
  class Entity
	{
    public:
      Entity() = default;

      Entity(entt::entity f_handle, Scene* f_scene)
      {
        m_EntityHandle = f_handle;
        m_Scene        = f_scene;
      }

      Entity(const Entity& f_other) = default;

      template<typename T, typename... Args>
      T& AddComponent(Args&&... f_args)
      {
        CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
        return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(f_args)...);
      }

      template<typename T>
      T& GetComponent()
      {
        CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
        return m_Scene->m_Registry.get<T>(m_EntityHandle);
      }

      template<typename T>
      bool HasComponent()
      {
        return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
      }

      template<typename T>
      void RemoveComponent()
      {
        CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
        m_Scene->m_Registry.remove<T>(m_EntityHandle);
      }

      operator bool() const { return m_EntityHandle != entt::null; }

    private:
      entt::entity m_EntityHandle{0};
      Scene*       m_Scene = nullptr;
	};
} // namespace Engine::Scene