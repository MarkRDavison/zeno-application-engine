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

		bool contains(const Vector2f& point) const
		{
			return
				position.x <= point.x &&
				position.y <= point.y &&
				point.x <= (position.x + size.x) &&
				point.y <= (position.y + size.y);
		}
	};

}