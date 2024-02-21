#include <zae/Game/Camera3DPerspective.hpp>
#include <zae/Engine/Devices/Windows.hpp>

namespace zae
{

	void Camera3DPerspective::Update(float delta)
	{
		auto ar = Windows::Get()->GetWindow(0)->GetAspectRatio();
		projectionMatrix = Matrix4::PerspectiveMatrix(this->fieldOfView, ar, this->nearPlane);
		projectionMatrix[1][1] *= -1;
		viewMatrix = Matrix4::ViewMatrix(position, rotation);
	}
}