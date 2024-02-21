#pragma once

#include <string>

struct Wave
{
	int amount;
	int remaining;
	std::string type;
	std::string spawn;
	float interval;
	float delay;
	float elapsed;
};