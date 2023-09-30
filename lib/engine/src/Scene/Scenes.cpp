#include <zae/Engine/Scene/Scenes.hpp>

namespace zae
{

	Scenes* Scenes::Instance = nullptr;

	void Scenes::AddScene(Scene* scene)
	{
		scenes.push_back(scene);
	}
	void Scenes::Update(float delta)
	{
		for (auto& scene : scenes)
		{
			scene->UpdateScene(delta);
		}
	}
}