#pragma once

#include <zae/Engine/Scene/Camera.hpp>

namespace zae
{

	class Camera3D : public Camera
	{
	public:
		Camera3D() :
			nearPlane(0.1f),
			farPlane(1000.0f),
			fieldOfView(Math::Radians(45.0f))
		{
		}


		float GetNearPlane() const { return nearPlane; }
		void SetNearPlane(float nearPlane) { this->nearPlane = nearPlane; }

		float GetFarPlane() const { return farPlane; }
		void SetFarPlane(float farPlane) { this->farPlane = farPlane; }

		float GetFieldOfView() const { return fieldOfView; }
		void SetFieldOfView(float fieldOfView) { this->fieldOfView = fieldOfView; }

		const Vector3f& GetPosition() const { return position; }
		const Vector3f& GetRotation() const { return rotation; }
		const Vector3f& GetVelocity() const { return velocity; }

	protected:
		float nearPlane, farPlane;
		float fieldOfView;

		Vector3f position;
		Vector3f rotation;
		Vector3f velocity;

	};

}