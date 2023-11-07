#pragma once

#include <zae/Core/Math/Vector2.hpp>

struct Tile
{

	zae::Vector2i position;
	std::string mesh;
	float rotation{ 0.0f };

};