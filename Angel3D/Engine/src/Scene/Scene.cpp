#include "Scene/Scene.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"

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

	Entity Scene::CreateEntity(const std::string& f_name)
	{
		Entity entity = { m_Registry.create(), this };

		entity.AddComponent<TransformComponent>();

		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = f_name.empty() ? "Entity" : f_name;

		return entity;
	}

	void Scene::OnUpdate(Engine::Core::Timestep ts)
	{
		Engine::Renderer::Camera *mainCamera      = nullptr;
		glm::mat4                *cameraTransform = nullptr;

		auto group = m_Registry.view<TransformComponent, CameraComponent>();
		for(auto entity : group)
		{
			auto& [transform, camera] = m_Registry.get<TransformComponent, CameraComponent>(entity);

			if(camera.PrimaryCamera)
			{
				mainCamera      = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}

		if(mainCamera)
		{
			Engine::Renderer::Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Engine::Renderer::Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Engine::Renderer::Renderer2D::EndScene();
		}
	}
} // namespace Engine::Scene