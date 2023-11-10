#pragma once

#include <optional>
#include "Tile.hpp"
#include "Round.hpp"

struct Level
{
	std::vector<Tile> tiles;
	std::vector<zae::Vector2i> path;
	std::optional<Round> round;
};