#pragma once

#include <cstdint>
#include <type_traits>

namespace zae {
template<typename T>
class Vector3;

template<typename T>
class Vector2 {
public:
	constexpr Vector2() = default;

	constexpr explicit Vector2(const T &a);

	constexpr Vector2(const T &x, const T &y);

	template<typename K, typename J>
	constexpr Vector2(const K &x, const J &y);

	template<typename K>
	constexpr Vector2(const Vector2<K> &source);

	template<typename K>
	constexpr Vector2(const Vector3<K> &source);

	template<typename K>
	constexpr auto Add(const Vector2<K> &other) const;

	template<typename K>
	constexpr auto Subtract(const Vector2<K> &other) const;

	template<typename K>
	constexpr auto Multiply(const Vector2<K> &other) const;

	template<typename K>
	constexpr auto Divide(const Vector2<K> &other) const;

	constexpr T Angle() const;

	template<typename K>
	constexpr auto Angle(const Vector2<K> &other) const;

	template<typename K>
	constexpr auto Dot(const Vector2<K> &other) const;

	template<typename K, typename J = float>
	constexpr auto Lerp(const Vector2<K> &other, const J &progression) const;

	template<typename K = float>
	constexpr auto Scale(const K &scalar) const;

	template<typename K = float>
	auto Rotate(const K &angle) const;

	template<typename K = float, typename J>
	auto Rotate(const K &angle, const Vector2<J> &rotationAxis) const;

	auto Normalize() const;

	constexpr auto LengthSquared() const;

	auto Length() const;

	auto Abs() const;

	constexpr auto Min() const;

	constexpr auto Max() const;

	constexpr auto MinMax() const;

	template<typename K>
	constexpr auto Min(const Vector2<K> &other);

	template<typename K>
	constexpr auto Max(const Vector2<K> &other);

	template<typename K>
	constexpr auto DistanceSquared(const Vector2<K> &other) const;

	template<typename K>
	auto Distance(const Vector2<K> &other) const;

	template<typename K>
	constexpr auto DistanceVector(const Vector2<K> &other) const;

	template<typename K>
	constexpr bool InTriangle(const Vector2<K> &v1, const Vector2<K> &v2, const Vector2<K> &v3) const;

	template<typename K, typename J>
	constexpr auto SmoothDamp(const Vector2<K> &target, const Vector2<J> &rate) const;

	auto CartesianToPolar() const;

	auto PolarToCartesian() const;

	constexpr const T &operator[](uint32_t index) const;
	constexpr T &operator[](uint32_t index);

	template<typename K>
	constexpr bool operator==(const Vector2<K> &other) const;
	template<typename K>
	constexpr bool operator!=(const Vector2<K> &other) const;

	template<typename U = T>
	constexpr auto operator-() const -> std::enable_if_t<std::is_signed_v<U>, Vector2>;
	template<typename U = T>
	constexpr auto operator~() const -> std::enable_if_t<std::is_integral_v<U>, Vector2>;

	template<typename K>
	constexpr Vector2 &operator+=(const Vector2<K> &other);
	template<typename K>
	constexpr Vector2 &operator-=(const Vector2<K> &other);
	template<typename K>
	constexpr Vector2 &operator*=(const Vector2<K> &other);
	template<typename K>
	constexpr Vector2 &operator/=(const Vector2<K> &other);
	constexpr Vector2 &operator+=(const T &other);
	constexpr Vector2 &operator-=(const T &other);
	constexpr Vector2 &operator*=(const T &other);
	constexpr Vector2 &operator/=(const T &other);

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Infinity;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;

	T x = 0, y = 0;
};

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int32_t>;
using Vector2ui = Vector2<uint32_t>;
using Vector2us = Vector2<uint16_t>;
}

#include "Vector2.inl"