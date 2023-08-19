#pragma once

#include <zae/Core/Math/Vector3.hpp>

namespace zae
{
	class Matrix2;
	class Matrix4;

	class Matrix3
	{
	public:
		Matrix3(float diagonal = 1.0f);

		Matrix3(const Matrix2& source);

		Matrix3(const Matrix4& source);

		explicit Matrix3(const float source[9]);

		explicit Matrix3(const Vector3f source[3]);

		Matrix3 Add(const Matrix3& other) const;

		Matrix3 Subtract(const Matrix3& other) const;

		Matrix3 Multiply(const Matrix3& other) const;

		Vector3f Multiply(const Vector3f& other) const;

		Matrix3 Divide(const Matrix3& other) const;

		Vector3f Transform(const Vector3f& other) const;

		Matrix3 Scale(const Vector3f& other) const;

		Matrix3 Negate() const;

		Matrix3 Inverse() const;

		Matrix3 Transpose() const;

		float Determinant() const;

		Matrix2 GetSubmatrix(uint32_t row, uint32_t col) const;

		const Vector3f& operator[](uint32_t index) const;
		Vector3f& operator[](uint32_t index);

		bool operator==(const Matrix3& other) const;
		bool operator!=(const Matrix3& other) const;

		Matrix3 operator-() const;

		friend Matrix3 operator+(const Matrix3& left, const Matrix3& right);
		friend Matrix3 operator-(const Matrix3& left, const Matrix3& right);
		friend Matrix3 operator*(const Matrix3& left, const Matrix3& right);
		friend Matrix3 operator/(const Matrix3& left, const Matrix3& right);
		friend Matrix3 operator*(const Vector3f& left, const Matrix3& right);
		friend Matrix3 operator/(const Vector3f& left, const Matrix3& right);
		friend Matrix3 operator*(const Matrix3& left, const Vector3f& right);
		friend Matrix3 operator/(const Matrix3& left, const Vector3f& right);
		friend Matrix3 operator*(float left, const Matrix3& right);
		friend Matrix3 operator/(float left, const Matrix3& right);
		friend Matrix3 operator*(const Matrix3& left, float right);
		friend Matrix3 operator/(const Matrix3& left, float right);

		Matrix3& operator+=(const Matrix3& other);
		Matrix3& operator-=(const Matrix3& other);
		Matrix3& operator*=(const Matrix3& other);
		Matrix3& operator/=(const Matrix3& other);
		Matrix3& operator*=(const Vector3f& other);
		Matrix3& operator/=(const Vector3f& other);
		Matrix3& operator*=(float other);
		Matrix3& operator/=(float other);

		friend std::ostream& operator<<(std::ostream& stream, const Matrix3& matrix);

		Vector3f rows[3];
	};
}

namespace std
{
	template<>
	struct hash<zae::Matrix3>
	{
		size_t operator()(const zae::Matrix3& matrix) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, matrix[0]);
			zae::Math::HashCombine(seed, matrix[1]);
			zae::Math::HashCombine(seed, matrix[2]);
			return seed;
		}
	};
}