#pragma once

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

class TowerPrefabs
{
	TowerPrefabs() = delete;
public:
	static zae::Entity* SpawnTestTower(zae::EntityHolder& entities, const zae::Vector2i& tile);

};