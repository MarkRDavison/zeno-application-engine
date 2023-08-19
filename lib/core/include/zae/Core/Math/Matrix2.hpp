#pragma once

#include <zae/Core/Math/Vector2.hpp>

namespace zae
{
	class Matrix3;
	class Matrix4;

	class Matrix2
	{
	public:
		Matrix2(float diagonal = 1.0f);

		Matrix2(const Matrix3& source);

		Matrix2(const Matrix4& source);

		explicit Matrix2(const float source[4]);

		explicit Matrix2(const Vector2f source[2]);

		Matrix2 Add(const Matrix2& other) const;

		Matrix2 Subtract(const Matrix2& other) const;

		Matrix2 Multiply(const Matrix2& other) const;

		Matrix2 Divide(const Matrix2& other) const;

		Vector2f Transform(const Vector2f& other) const;

		Matrix2 Scale(const Vector2f& other) const;

		Matrix2 Negate() const;

		Matrix2 Inverse() const;

		Matrix2 Transpose() const;

		float Determinant() const;

		float GetSubmatrix(uint32_t row, uint32_t col) const;

		const Vector2f& operator[](uint32_t index) const;
		Vector2f& operator[](uint32_t index);

		bool operator==(const Matrix2& other) const;
		bool operator!=(const Matrix2& other) const;

		Matrix2 operator-() const;

		friend Matrix2 operator+(const Matrix2& left, const Matrix2& right);
		friend Matrix2 operator-(const Matrix2& left, const Matrix2& right);
		friend Matrix2 operator*(const Matrix2& left, const Matrix2& right);
		friend Matrix2 operator/(const Matrix2& left, const Matrix2& right);
		friend Matrix2 operator*(const Vector2f& left, const Matrix2& right);
		friend Matrix2 operator/(const Vector2f& left, const Matrix2& right);
		friend Matrix2 operator*(const Matrix2& left, const Vector2f& right);
		friend Matrix2 operator/(const Matrix2& left, const Vector2f& right);
		friend Matrix2 operator*(float left, const Matrix2& right);
		friend Matrix2 operator/(float left, const Matrix2& right);
		friend Matrix2 operator*(const Matrix2& left, float right);
		friend Matrix2 operator/(const Matrix2& left, float right);

		Matrix2& operator+=(const Matrix2& other);
		Matrix2& operator-=(const Matrix2& other);
		Matrix2& operator*=(const Matrix2& other);
		Matrix2& operator/=(const Matrix2& other);
		Matrix2& operator*=(const Vector2f& other);
		Matrix2& operator/=(const Vector2f& other);
		Matrix2& operator*=(float other);
		Matrix2& operator/=(float other);

		friend std::ostream& operator<<(std::ostream& stream, const Matrix2& matrix);

		Vector2f rows[2];
	};
}

namespace std
{
	template<>
	struct hash<zae::Matrix2>
	{
		size_t operator()(const zae::Matrix2& matrix) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, matrix[0]);
			zae::Math::HashCombine(seed, matrix[1]);
			return seed;
		}
	};
}