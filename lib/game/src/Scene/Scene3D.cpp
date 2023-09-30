#include <zae/Game/Scene/Scene3D.hpp>

namespace zae
{

	Scene3D::Scene3D(
		Camera3D* camera
	) : Scene(
		camera
	),
		camera(camera)
	{

	}
	void Scene3D::Update(float delta)
	{
		systems.ForEach(
			[](auto typeId, auto system)
			{
				if (system->IsEnabled())
				{
					system->Update();
				}
			});

		entities.Update();
	}
}