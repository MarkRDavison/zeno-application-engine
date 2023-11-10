#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>

class PathFollowerComponent : public zae::Component
{
public:
	float speed;

	unsigned pathIndex = std::numeric_limits<unsigned>::max();
};