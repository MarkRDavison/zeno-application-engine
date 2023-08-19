#pragma once

#include <cassert>
#include <sstream>
#include <iomanip>

#include <zae/Core/Math/Math.hpp>

namespace zae
{
	class Colour
	{
	public:
		enum class Type
		{
			RGBA, ARGB, RGB
		};

		Colour() = default;

		constexpr Colour(float r, float g, float b, float a = 1.0f) :
			r(r),
			g(g),
			b(b),
			a(a)
		{
		}

		constexpr Colour(uint32_t i, Type type = Type::RGB)
		{
			switch (type)
			{
			case Type::RGBA:
				r = static_cast<float>((uint8_t)(i >> 24 & 0xFF)) / 255.0f;
				g = static_cast<float>((uint8_t)(i >> 16 & 0xFF)) / 255.0f;
				b = static_cast<float>((uint8_t)(i >> 8 & 0xFF)) / 255.0f;
				a = static_cast<float>((uint8_t)(i & 0xFF)) / 255.0f;
				break;
			case Type::ARGB:
				r = static_cast<float>((uint8_t)(i >> 16)) / 255.0f;
				g = static_cast<float>((uint8_t)(i >> 8)) / 255.0f;
				b = static_cast<float>((uint8_t)(i & 0xFF)) / 255.0f;
				a = static_cast<float>((uint8_t)(i >> 24)) / 255.0f;
				break;
			case Type::RGB:
				r = static_cast<float>((uint8_t)(i >> 16)) / 255.0f;
				g = static_cast<float>((uint8_t)(i >> 8)) / 255.0f;
				b = static_cast<float>((uint8_t)(i & 0xFF)) / 255.0f;
				a = 1.0f;
				break;
			default:
				throw std::runtime_error("Unknown Color type");
			}
		}

		Colour(std::string hex, float a = 1.0f) :
			a(a)
		{
			if (hex[0] == '#')
			{
				hex.erase(0, 1);
			}

			assert(hex.size() == 6);
			auto hexValue = std::stoul(hex, nullptr, 16);

			r = static_cast<float>((hexValue >> 16) & 0xff) / 255.0f;
			g = static_cast<float>((hexValue >> 8) & 0xff) / 255.0f;
			b = static_cast<float>((hexValue >> 0) & 0xff) / 255.0f;
		}

		constexpr Colour Lerp(const Colour& other, float progression) const
		{
			auto ta = *this * (1.0f - progression);
			auto tb = other * progression;
			return ta + tb;
		}

		Colour Normalize() const
		{
			auto l = Length();

			if (l == 0.0f)
				throw std::runtime_error("Can't normalize a zero length vector");

			return { r / l, g / l, b / l, a / l };
		}

		constexpr float Length2() const
		{
			return r * r + g * g + b * b + a * a;
		}

		float Length() const
		{
			return std::sqrt(Length2());
		}

		constexpr Colour SmoothDamp(const Colour& target, const Colour& rate) const
		{
			return Math::SmoothDamp(*this, target, rate);
		}

		Colour GetUnit() const
		{
			auto l = Length();
			return { r / l, g / l, b / l, a / l };
		}

		constexpr uint32_t GetInt(Type type = Type::RGBA) const
		{
			switch (type)
			{
			case Type::RGBA:
				return (static_cast<uint8_t>(r * 255.0f) << 24) | (static_cast<uint8_t>(g * 255.0f) << 16) | (static_cast<uint8_t>(b * 255.0f) << 8) | (static_cast<uint8_t>(a * 255.0f) &
					0xFF);
			case Type::ARGB:
				return (static_cast<uint8_t>(a * 255.0f) << 24) | (static_cast<uint8_t>(r * 255.0f) << 16) | (static_cast<uint8_t>(g * 255.0f) << 8) | (static_cast<uint8_t>(b * 255.0f) &
					0xFF);
			case Type::RGB:
				return (static_cast<uint8_t>(r * 255.0f) << 16) | (static_cast<uint8_t>(g * 255.0f) << 8) | (static_cast<uint8_t>(b * 255.0f) & 0xFF);
			default:
				throw std::runtime_error("Unknown Color type");
			}
		}

		std::string GetHex() const
		{
			std::stringstream stream;
			stream << "#";

			auto hexValue = ((static_cast<uint32_t>(r * 255.0f) & 0xff) << 16) +
				((static_cast<uint32_t>(g * 255.0f) & 0xff) << 8) +
				((static_cast<uint32_t>(b * 255.0f) & 0xff) << 0);
			stream << std::hex << std::setfill('0') << std::setw(6) << hexValue;

			return stream.str();
		}

		constexpr float operator[](uint32_t i) const
		{
			assert(i < 4 && "Colour subscript out of range");
			return i == 0 ? r : i == 1 ? g : i == 2 ? b : a;
		}
		constexpr float& operator[](uint32_t i)
		{
			assert(i < 4 && "Colour subscript out of range");
			return i == 0 ? r : i == 1 ? g : i == 2 ? b : a;
		}

		constexpr bool operator==(const Colour& rhs) const;
		constexpr bool operator!=(const Colour& rhs) const;

		constexpr friend Colour operator+(const Colour& lhs, const Colour& rhs);
		constexpr friend Colour operator-(const Colour& lhs, const Colour& rhs);
		constexpr friend Colour operator*(const Colour& lhs, const Colour& rhs);
		constexpr friend Colour operator/(const Colour& lhs, const Colour& rhs);
		constexpr friend Colour operator+(float lhs, const Colour& rhs);
		constexpr friend Colour operator-(float lhs, const Colour& rhs);
		constexpr friend Colour operator*(float lhs, const Colour& rhs);
		constexpr friend Colour operator/(float lhs, const Colour& rhs);
		constexpr friend Colour operator+(const Colour& lhs, float rhs);
		constexpr friend Colour operator-(const Colour& lhs, float rhs);
		constexpr friend Colour operator*(const Colour& lhs, float rhs);
		constexpr friend Colour operator/(const Colour& lhs, float rhs);

		constexpr Colour& operator+=(const Colour& rhs);
		constexpr Colour& operator-=(const Colour& rhs);
		constexpr Colour& operator*=(const Colour& rhs);
		constexpr Colour& operator/=(const Colour& rhs);
		constexpr Colour& operator+=(float rhs);
		constexpr Colour& operator-=(float rhs);
		constexpr Colour& operator*=(float rhs);
		constexpr Colour& operator/=(float rhs);

		friend std::ostream& operator<<(std::ostream& stream, const Colour& colour);

		static const Colour Clear;
		static const Colour Black;
		static const Colour Grey;
		static const Colour Silver;
		static const Colour White;
		static const Colour Maroon;
		static const Colour Red;
		static const Colour Olive;
		static const Colour Yellow;
		static const Colour Green;
		static const Colour Lime;
		static const Colour Teal;
		static const Colour Aqua;
		static const Colour Navy;
		static const Colour Blue;
		static const Colour Purple;
		static const Colour Fuchsia;

		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
	};
}

#include "Colour.inl"