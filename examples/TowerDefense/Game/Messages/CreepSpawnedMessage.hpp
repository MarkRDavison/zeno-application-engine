#pragma once

#include <string>
#include <zae/Engine/Scene/Entity/Entity.hpp>

struct CreepSpawnedMessage
{
	zae::Entity* entity;
	std::string type;
	std::string spawn;
};