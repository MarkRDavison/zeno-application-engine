#pragma once
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>
#include "../Game/Data/Level.hpp"

class LevelInstantiation
{
	LevelInstantiation() = default;
public:
	static std::shared_ptr<Level> CreateExampleLevel(zae::EntityHolder& entities);
};