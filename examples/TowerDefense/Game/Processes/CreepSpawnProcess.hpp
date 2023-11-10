#pragma once

#include <memory>
#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>
#include "../Data/Level.hpp"

class CreepSpawnProcess : zae::NonCopyable
{
public:
	CreepSpawnProcess(std::shared_ptr<Level> level, zae::EntityHolder& entities);

	void Update();

	void SpawnCreep(const std::string& type, const std::string& spawn);

private:
	std::shared_ptr<Level> level;
	zae::EntityHolder& entities;
	bool recheckCreeps;
};