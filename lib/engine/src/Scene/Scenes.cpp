#include <zae/Engine/Scene/Scenes.hpp>

namespace zae
{

	Scenes* Scenes::Instance = nullptr;

	void Scenes::SetScene(std::unique_ptr<Scene> scene)
	{
		this->nextScene = std::move(scene);
	}

	const std::unique_ptr<Scene>& Scenes::GetScene()
	{
		return scene;
	}

	void Scenes::Update(float delta)
	{
		if (scene != nullptr)
		{
			scene->UpdateScene(delta);
		}

		if (nextScene != nullptr)
		{
			scene = std::move(nextScene);
			nextScene = nullptr;
		}
	}
}