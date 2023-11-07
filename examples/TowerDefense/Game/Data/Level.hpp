#pragma once

#include "Tile.hpp"

struct Level
{
	std::vector<Tile> tiles;
	std::vector<zae::Vector2i> path;
};