#include "Scene/Scene.h"
#include "Scene/Components.h"

#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Engine::Scene
{
  static void DoMath(const glm::mat4& transform)
	{
	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
	}

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Engine::Core::Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Engine::Renderer::Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
} // namespace Engine::Scene