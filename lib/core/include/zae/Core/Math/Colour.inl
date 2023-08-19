#pragma once

#include <zae/Core/Math/Colour.hpp>

namespace zae
{
	constexpr bool Colour::operator==(const Colour& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
	}

	constexpr bool Colour::operator!=(const Colour& rhs) const
	{
		return !operator==(rhs);
	}

	constexpr Colour operator+(const Colour& lhs, const Colour& rhs)
	{
		return { lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a };
	}

	constexpr Colour operator-(const Colour& lhs, const Colour& rhs)
	{
		return { lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a };
	}

	constexpr Colour operator*(const Colour& lhs, const Colour& rhs)
	{
		return { lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a };
	}

	constexpr Colour operator/(const Colour& lhs, const Colour& rhs)
	{
		return { lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b, lhs.a / rhs.a };
	}

	constexpr Colour operator+(float lhs, const Colour& rhs)
	{
		return Colour(lhs, lhs, lhs, 0.0f) + rhs;
	}

	constexpr Colour operator-(float lhs, const Colour& rhs)
	{
		return Colour(lhs, lhs, lhs, 0.0f) - rhs;
	}

	constexpr Colour operator*(float lhs, const Colour& rhs)
	{
		return Colour(lhs, lhs, lhs) * rhs;
	}

	constexpr Colour operator/(float lhs, const Colour& rhs)
	{
		return Colour(lhs, lhs, lhs) / rhs;
	}

	constexpr Colour operator+(const Colour& lhs, float rhs)
	{
		return lhs + Colour(rhs, rhs, rhs, 0.0f);
	}

	constexpr Colour operator-(const Colour& lhs, float rhs)
	{
		return lhs - Colour(rhs, rhs, rhs, 0.0f);
	}

	constexpr Colour operator*(const Colour& lhs, float rhs)
	{
		return lhs * Colour(rhs, rhs, rhs);
	}

	constexpr Colour operator/(const Colour& lhs, float rhs)
	{
		return lhs / Colour(rhs, rhs, rhs);
	}

	constexpr Colour& Colour::operator+=(const Colour& rhs)
	{
		return *this = *this + rhs;
	}

	constexpr Colour& Colour::operator-=(const Colour& rhs)
	{
		return *this = *this - rhs;
	}

	constexpr Colour& Colour::operator*=(const Colour& rhs)
	{
		return *this = *this * rhs;
	}

	constexpr Colour& Colour::operator/=(const Colour& rhs)
	{
		return *this = *this / rhs;
	}

	constexpr Colour& Colour::operator+=(float rhs)
	{
		return *this = *this + rhs;
	}

	constexpr Colour& Colour::operator-=(float rhs)
	{
		return *this = *this - rhs;
	}

	constexpr Colour& Colour::operator*=(float rhs)
	{
		return *this = *this * rhs;
	}

	constexpr Colour& Colour::operator/=(float rhs)
	{
		return *this = *this / rhs;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Colour& colour)
	{
		return stream << colour.r << ", " << colour.g << ", " << colour.b << ", " << colour.a;
	}
}

namespace std
{
	template<>
	struct hash<zae::Colour>
	{
		size_t operator()(const zae::Colour& colour) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, colour.r);
			zae::Math::HashCombine(seed, colour.g);
			zae::Math::HashCombine(seed, colour.b);
			zae::Math::HashCombine(seed, colour.a);
			return seed;
		}
	};
}