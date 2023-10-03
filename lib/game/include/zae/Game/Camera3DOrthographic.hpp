#pragma once

#include <zae/Engine/Scene/Camera.hpp>
#include <zae/Core/Math/Vector3.hpp>

namespace zae
{

	class Camera3DOrthographic : public Camera
	{
	public:
		void SetPosition(Vector3f position) { this->position = position; }
		Vector3f GetPosition() const { return position; }

	private:
		Vector3f position;
	};

}