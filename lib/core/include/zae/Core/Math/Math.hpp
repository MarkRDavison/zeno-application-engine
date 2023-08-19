#pragma once

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <functional>

namespace zae
{
	class Math
	{
	public:
		template<typename T>
		constexpr static T PI = static_cast<T>(3.14159265358979323846264338327950288L);

		Math() = delete;

		static float Random(float min = 0.0f, float max = 1.0f);

		static float RandomNormal(float standardDeviation, float mean);

		static float RandomLog(float min, float max);

		template<typename T = float>
		constexpr static T Radians(const T& degrees)
		{
			return static_cast<T>(degrees * PI<long double> / 180);
		}

		template<typename T = float>
		constexpr static T Degrees(const T& radians)
		{
			return static_cast<T>(radians * 180 / PI<long double>);
		}

		template<typename T = float>
		static T WrapDegrees(const T& degrees)
		{
			auto x = std::fmod(degrees, 360);

			if (x < 0)
			{
				x += 360;
			}

			return static_cast<T>(x);
		}

		template<typename T = float>
		static T WrapRadians(const T& radians)
		{
			auto x = std::fmod(radians, 2 * PI<T>);

			if (x < 0)
			{
				x += 2 * PI<T>;
			}

			return static_cast<T>(x);
		}

		template<typename T = float>
		static T RoundToPlace(const T& value, int32_t place)
		{
			auto placeMul = std::pow(10, place);
			return static_cast<T>(std::round(value * placeMul) / placeMul);
		}

		template<typename T = float>
		static T Deadband(const T& min, const T& value)
		{
			return std::fabs(value) >= std::fabs(min) ? value : 0.0f;
		}

		template<typename T = float, typename K = float>
		static bool AlmostEqual(const T& a, const T& b, const K& eps)
		{
			return std::fabs(a - b) < eps;
		}

		template<typename T = float, typename K = float>
		constexpr static auto SmoothDamp(const T& current, const T& target, const K& rate)
		{
			return current + ((target - current) * rate);
		}

		template<typename T = float, typename K = float>
		constexpr static auto Lerp(const T& a, const T& b, const K& factor)
		{
			return a * (1 - factor) + b * factor;
		}

		template<typename T = float, typename K = float>
		static auto CosLerp(const T& a, const T& b, const K& factor)
		{
			auto ft = factor * PI<T>;
			auto f = 1 - std::cos(ft) / 2;
			return (a * (1 - f)) + (b * f);
		}

		template<typename T = float, typename K = float>
		constexpr static auto SmoothlyStep(const T& edge0, const T& edge1, const K& x)
		{
			auto s = std::clamp((x - edge0) / (edge1 - edge0), 0, 1);
			return s * s * (3 - 2 * s);
		}

		template<typename T = float, typename K = float>
		static auto CosFromSin(const T& sin, const K& angle)
		{
			// sin(x)^2 + cos(x)^2 = 1
			auto cos = std::sqrt(1 - sin * sin);
			auto a = angle + (PI<T> / 2);
			auto b = a - static_cast<int32_t>(a / (2 * PI<T>)) * (2 * PI<T>);

			if (b < 0)
			{
				b = (2 * PI<T>) + b;
			}

			if (b >= PI<T>)
			{
				return -cos;
			}

			return cos;
		}

		template<typename T>
		static void HashCombine(std::size_t& seed, const T& v) noexcept
		{
			std::hash<T> hasher;
			seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
	};
}