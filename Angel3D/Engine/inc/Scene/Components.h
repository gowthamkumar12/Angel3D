#pragma once

#include "Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Engine::Scene
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent()                    = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent()                          = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent()                               = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		Engine::Renderer::Camera Camera;
		bool                     PrimaryCamera = true; // TODO:Think about moving into the scene.

		CameraComponent()                       = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& f_projection)
			: Camera(f_projection) {}
	};
}