#pragma once

#include <zae/Core/Math/Vector2.hpp>

namespace zae
{

	struct Rect
	{
		Rect() : Rect({}, {}) {}
		Rect(const Vector2f& position, const Vector2f& size = {}) :
			position(position),
			size(size)
		{

		}

		Vector2f position;
		Vector2f size;
	};

}