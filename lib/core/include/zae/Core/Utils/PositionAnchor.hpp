#pragma once

#include <cstdint>

namespace zae
{

	enum class PositionAnchor : uint8_t
	{
		NONE = 0,
		LEFT = 1,
		RIGHT = 2,
		TOP = 4,
		BOTTOM = 8,
		CENTERX = 16,
		CENTERY = 32,

		CENTER = CENTERX | CENTERY
	};

}