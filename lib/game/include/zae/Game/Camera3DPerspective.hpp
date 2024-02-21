#pragma once

#include <zae/Engine/Scene/Camera.hpp>
#include <zae/Core/Math/Vector3.hpp>

namespace zae
{

	class Camera3DPerspective : public Camera
	{
	public:
		Camera3DPerspective() :
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

		void SetPosition(const Vector3f& position) { this->position = position; }
		void SetRotation(const Vector3f& rotation) { this->rotation = rotation; }

		void Update(float delta) override;

	protected:
		Vector3f position;
		Vector3f rotation;

		float nearPlane, farPlane;
		float fieldOfView;
	};

}