#pragma once

#include <zae/Core/Math/Vector3.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

class ProjectilePrefabs
{
	ProjectilePrefabs() = delete;
public:
	static zae::Entity* SpawnTestProjectile(zae::EntityHolder& entities, const zae::Vector3f& origin, zae::Entity *target);

};