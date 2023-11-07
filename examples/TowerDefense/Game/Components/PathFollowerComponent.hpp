#pragma once

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Engine/Scene/Entity/Component.hpp>

class PathFollowerComponent : zae::Component
{
public:
	float speed;
	zae::Vector2i lastTile;
	zae::Vector2i nextTile;
};