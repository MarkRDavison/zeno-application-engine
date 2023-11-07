#pragma once
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

class LevelInstantiation
{
	LevelInstantiation() = default;
public:
	static void CreateExampleLevel(zae::EntityHolder& entities);
};