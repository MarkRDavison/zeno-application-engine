#pragma once

#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

class CreepPrefabs
{
	CreepPrefabs() = delete;
public:
	static zae::Entity* SpawnTestCreep(zae::EntityHolder& entities);

};