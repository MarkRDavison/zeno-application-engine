#pragma once

#include <cstdint>
#include <type_traits>

namespace zae {
	template<typename T>
	class Vector2;

	template<typename T>
	class Vector3;

	template<typename T>
	class Vector4 {
	public:
		constexpr Vector4() = default;

		constexpr explicit Vector4(const T &a);

		constexpr Vector4(const T &x, const T &y, const T &z, const T &w = 1);

		template<typename K, typename J, typename H, typename F>
		constexpr Vector4(const K &x, const J &y, const H &z, const F &w);

		template<typename K, typename J>
		constexpr Vector4(const Vector2<K> &left, const Vector2<J> &right = Vector2<K>::Up);

		template<typename K, typename J = T>
		explicit constexpr Vector4(const Vector3<K> &source, const J &w = 1);

		template<typename K>
		constexpr Vector4(const Vector4<K> &source);

		template<typename K>
		constexpr auto Add(const Vector4<K> &other) const;

		template<typename K>
		constexpr auto Subtract(const Vector4<K> &other) const;

		template<typename K>
		constexpr auto Multiply(const Vector4<K> &other) const;

		template<typename K>
		constexpr auto Divide(const Vector4<K> &other) const;

		template<typename K>
		auto Angle(const Vector4<K> &other) const;

		template<typename K>
		constexpr auto Dot(const Vector4<K> &other) const;

		template<typename K, typename J = float>
		constexpr auto Lerp(const Vector4<K> &other, const J &progression) const;

		template<typename K = float>
		constexpr auto Scale(const K &scalar) const;

		auto Normalize() const;

		constexpr auto LengthSquared() const;

		auto Length() const;

		auto Abs() const;

		constexpr auto Min() const;

		constexpr auto Max() const;

		constexpr auto MinMax() const;

		template<typename K>
		constexpr auto Min(const Vector4<K> &other);

		template<typename K>
		constexpr auto Max(const Vector4<K> &other);

		template<typename K>
		constexpr auto DistanceSquared(const Vector4<K> &other) const;

		template<typename K>
		auto Distance(const Vector4<K> &other) const;

		template<typename K>
		constexpr auto DistanceVector(const Vector4<K> &other) const;

		template<typename K, typename J>
		constexpr auto SmoothDamp(const Vector4<K> &target, const Vector4<J> &rate) const;

		constexpr const T &operator[](uint32_t index) const;
		constexpr T &operator[](uint32_t index);

		template<typename K>
		constexpr bool operator==(const Vector4<K> &other) const;
		template<typename K>
		constexpr bool operator!=(const Vector4<K> &other) const;

		template<typename U = T>
		constexpr auto operator-() const -> std::enable_if_t<std::is_signed_v<U>, Vector4>;
		template<typename U = T>
		constexpr auto operator~() const -> std::enable_if_t<std::is_integral_v<U>, Vector4>;

		template<typename K>
		constexpr Vector4 &operator+=(const Vector4<K> &other);
		template<typename K>
		constexpr Vector4 &operator-=(const Vector4<K> &other);
		template<typename K>
		constexpr Vector4 &operator*=(const Vector4<K> &other);
		template<typename K>
		constexpr Vector4 &operator/=(const Vector4<K> &other);
		constexpr Vector4 &operator+=(const T &other);
		constexpr Vector4 &operator-=(const T &other);
		constexpr Vector4 &operator*=(const T &other);
		constexpr Vector4 &operator/=(const T &other);

		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 Infinity;

		T x = 0, y = 0, z = 0, w = 1;
	};

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int32_t>;
	using Vector4ui = Vector4<uint32_t>;
}

#include "Vector4.inl"