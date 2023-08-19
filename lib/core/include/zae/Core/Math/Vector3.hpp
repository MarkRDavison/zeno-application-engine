#pragma once

#include <cstdint>
#include <type_traits>

namespace zae {
	template<typename T>
	class Vector2;

	template<typename T>
	class Vector4;

	template<typename T>
	class Vector3 {
	public:
		constexpr Vector3() = default;

		constexpr explicit Vector3(const T &a);

		constexpr Vector3(const T &x, const T &y, const T &z);

		template<typename K, typename J, typename H>
		constexpr Vector3(const K &x, const J &y, const H &z);

		template<typename K, typename J = T>
		explicit constexpr Vector3(const Vector2<K> &source, const J &z = 0);

		template<typename K>
		constexpr Vector3(const Vector3<K> &source);

		template<typename K>
		constexpr Vector3(const Vector4<K> &source);

		template<typename K>
		constexpr auto Add(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto Subtract(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto Multiply(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto Divide(const Vector3<K> &other) const;

		template<typename K>
		auto Angle(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto Dot(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto Cross(const Vector3<K> &other) const;

		template<typename K, typename J = float>
		constexpr auto Lerp(const Vector3<K> &other, const J &progression) const;

		template<typename K = float>
		constexpr auto Scale(const K &scalar) const;

		//template<typename K = float>
		//auto Rotate(const Vector3<K> &angle) const; 

		auto Normalize() const;

		constexpr auto LengthSquared() const;

		auto Length() const;

		auto Abs() const;

		constexpr auto Min() const;

		constexpr auto Max() const;

		constexpr auto MinMax() const;

		template<typename K>
		constexpr auto Min(const Vector3<K> &other);

		template<typename K>
		constexpr auto Max(const Vector3<K> &other);

		template<typename K>
		constexpr auto DistanceSquared(const Vector3<K> &other) const;

		template<typename K>
		auto Distance(const Vector3<K> &other) const;

		template<typename K>
		constexpr auto DistanceVector(const Vector3<K> &other) const;

		template<typename K, typename J>
		constexpr auto SmoothDamp(const Vector3<K> &target, const Vector3<J> &rate) const;

		auto CartesianToPolar() const;

		auto PolarToCartesian() const;

		constexpr const T &operator[](uint32_t index) const;
		constexpr T &operator[](uint32_t index);

		template<typename K>
		constexpr bool operator==(const Vector3<K> &other) const;
		template<typename K>
		constexpr bool operator!=(const Vector3<K> &other) const;

		template<typename U = T>
		constexpr auto operator-() const -> std::enable_if_t<std::is_signed_v<U>, Vector3>;
		template<typename U = T>
		constexpr auto operator~() const -> std::enable_if_t<std::is_integral_v<U>, Vector3>;

		template<typename K>
		constexpr Vector3 &operator+=(const Vector3<K> &other);
		template<typename K>
		constexpr Vector3 &operator-=(const Vector3<K> &other);
		template<typename K>
		constexpr Vector3 &operator*=(const Vector3<K> &other);
		template<typename K>
		constexpr Vector3 &operator/=(const Vector3<K> &other);
		constexpr Vector3 &operator+=(const T &other);
		constexpr Vector3 &operator-=(const T &other);
		constexpr Vector3 &operator*=(const T &other);
		constexpr Vector3 &operator/=(const T &other);

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Infinity;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Front;
		static const Vector3 Back;

		T x = 0, y = 0, z = 0;
	};

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int32_t>;
	using Vector3ui = Vector3<uint32_t>;
}

#include "Vector3.inl"