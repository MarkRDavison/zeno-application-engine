#pragma once

#include <zae/Core/Math/Matrix4.hpp>

namespace zae
{

	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void Start() {}
		virtual void Update(float delta) {}

		const Matrix4& GetViewMatrix() const { return viewMatrix; }

		const Matrix4& GetProjectionMatrix() const { return projectionMatrix; }

	protected:
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;
	};

}