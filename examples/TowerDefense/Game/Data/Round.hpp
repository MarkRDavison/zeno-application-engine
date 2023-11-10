#pragma once

#include <vector>
#include "Wave.hpp"

struct Round
{
	std::vector<Wave> waves;
	bool allSpawned;
};