#include <zae/Engine/Scene/Scenes.hpp>

namespace zae
{

	Scenes* Scenes::Instance = nullptr;

	void Scenes::SetScene(Scene* scene)
	{
		this->scene = scene;
	}

	Scene* Scenes::GetScene()
	{
		return scene;
	}

	void Scenes::Update(float delta)
	{
		if (scene != nullptr)
		{
			scene->UpdateScene(delta);
		}
	}
}