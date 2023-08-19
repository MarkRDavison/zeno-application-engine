#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Core/Math/Vector3.hpp>

namespace zae
{
	/**
	 * @brief A vector like object of the form w + xi + yj + zk, where w, x, y, z are real numbers and i, j, k are imaginary units.
	 */
	class Quaternion
	{
	public:
		Quaternion() = default;

		Quaternion(float x, float y, float z, float w);

		explicit Quaternion(const Vector3f& source);

		Quaternion(const Matrix4& source);

		Quaternion(const Vector3f& axisX, const Vector3f& axisY, const Vector3f& axisZ);

		Quaternion MultiplyInverse(const Quaternion& other) const;

		float Dot(const Quaternion& other) const;

		Quaternion Slerp(const Quaternion& other, float progression) const;

		Quaternion Normalize() const;

		float LengthSquared() const;

		float Length() const;

		float MaxComponent() const;

		float MinComponent() const;

		Matrix4 ToMatrix() const;

		Matrix4 ToRotationMatrix() const;

		Vector3f ToEuler() const;

		float operator[](uint32_t index) const;
		float& operator[](uint32_t index);

		bool operator==(const Quaternion& rhs) const;
		bool operator!=(const Quaternion& rhs) const;

		Quaternion operator-() const;

		friend Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
		friend Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
		friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
		friend Vector3f operator*(const Vector3f& lhs, const Quaternion& rhs);
		friend Vector3f operator*(const Quaternion& lhs, const Vector3f& rhs);
		friend Quaternion operator*(float lhs, const Quaternion& rhs);
		friend Quaternion operator*(const Quaternion& lhs, float rhs);

		Quaternion& operator*=(const Quaternion& rhs);
		Quaternion& operator*=(float rhs);

		friend std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);

		static const Quaternion Zero;
		static const Quaternion One;
		static const Quaternion PositiveInfinity;
		static const Quaternion NegativeInfinity;

		float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
	};
}

namespace std
{
	template<>
	struct hash<zae::Quaternion>
	{
		size_t operator()(const zae::Quaternion& quaternion) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, quaternion.x);
			zae::Math::HashCombine(seed, quaternion.y);
			zae::Math::HashCombine(seed, quaternion.z);
			zae::Math::HashCombine(seed, quaternion.w);
			return seed;
		}
	};
}