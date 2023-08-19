#pragma once

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Core/Math/Vector3.hpp>
#include <zae/Core/Math/Vector4.hpp>

namespace zae
{
	class Matrix2;
	class Matrix3;

	class Matrix4
	{
	public:
		Matrix4(float diagonal = 1.0f);

		Matrix4(const Matrix2& source);

		Matrix4(const Matrix3& source);

		explicit Matrix4(const float source[16]);

		explicit Matrix4(const Vector4f source[4]);

		Matrix4 Add(const Matrix4& other) const;

		Matrix4 Subtract(const Matrix4& other) const;

		Matrix4 Multiply(const Matrix4& other) const;

		Vector4f Multiply(const Vector4f& other) const;

		Matrix4 Divide(const Matrix4& other) const;

		Vector4f Transform(const Vector4f& other) const;

		Matrix4 Translate(const Vector2f& other) const;

		Matrix4 Translate(const Vector3f& other) const;

		Matrix4 Scale(const Vector3f& other) const;

		Matrix4 Scale(const Vector4f& other) const;

		Matrix4 Rotate(float angle, const Vector3f& axis) const;

		Matrix4 Negate() const;

		Matrix4 Inverse() const;

		Matrix4 Transpose() const;

		float Determinant() const;

		Matrix3 GetSubmatrix(uint32_t row, uint32_t col) const;

		static Matrix4 TransformationMatrix(const Vector3f& translation, const Vector3f& rotation, const Vector3f& scale);

		static Matrix4 PerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar);

		static Matrix4 PerspectiveMatrix(float fov, float aspectRatio, float zNear);

		static Matrix4 OrthographicMatrix(float left, float right, float bottom, float top, float zNear, float zFar);

		static Matrix4 FrustumMatrix(float left, float right, float bottom, float top, float zNear, float zFar);

		static Matrix4 ViewMatrix(const Vector3f& position, const Vector3f& rotation);

		static Vector3f Project(const Vector3f& worldSpace, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		static Vector3f Unproject(const Vector3f& screenSpace, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		static Matrix4 LookAt(const Vector3f& eye, const Vector3f& centre, const Vector3f& up = Vector3f::Up);

		const Vector4f& operator[](uint32_t index) const;
		Vector4f& operator[](uint32_t index);

		bool operator==(const Matrix4& other) const;
		bool operator!=(const Matrix4& other) const;

		Matrix4 operator-() const;

		friend Matrix4 operator+(const Matrix4& left, const Matrix4& right);
		friend Matrix4 operator-(const Matrix4& left, const Matrix4& right);
		friend Matrix4 operator*(const Matrix4& left, const Matrix4& right);
		friend Matrix4 operator/(const Matrix4& left, const Matrix4& right);
		friend Matrix4 operator*(const Vector4f& left, const Matrix4& right);
		friend Matrix4 operator/(const Vector4f& left, const Matrix4& right);
		friend Matrix4 operator*(const Matrix4& left, const Vector4f& right);
		friend Matrix4 operator/(const Matrix4& left, const Vector4f& right);
		friend Matrix4 operator*(float left, const Matrix4& right);
		friend Matrix4 operator/(float left, const Matrix4& right);
		friend Matrix4 operator*(const Matrix4& left, float right);
		friend Matrix4 operator/(const Matrix4& left, float right);

		Matrix4& operator+=(const Matrix4& other);
		Matrix4& operator-=(const Matrix4& other);
		Matrix4& operator*=(const Matrix4& other);
		Matrix4& operator/=(const Matrix4& other);
		Matrix4& operator*=(const Vector4f& other);
		Matrix4& operator/=(const Vector4f& other);
		Matrix4& operator*=(float other);
		Matrix4& operator/=(float other);

		friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);

		Vector4f rows[4];
	};
}

namespace std
{
	template<>
	struct hash<zae::Matrix4>
	{
		size_t operator()(const zae::Matrix4& matrix) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, matrix[0]);
			zae::Math::HashCombine(seed, matrix[1]);
			zae::Math::HashCombine(seed, matrix[2]);
			zae::Math::HashCombine(seed, matrix[3]);
			return seed;
		}
	};
}