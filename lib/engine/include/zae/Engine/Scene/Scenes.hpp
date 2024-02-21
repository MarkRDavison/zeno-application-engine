#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Scene/Scene.hpp>
#include <vector>

namespace zae
{

	class Scenes : NonCopyable
	{
		Scenes() = default;
	public:
		static Scenes* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new Scenes();
			}

			return Instance;
		}


		void SetScene(std::unique_ptr<Scene> scene);
		const std::unique_ptr<Scene>& GetScene();
		void Update(float delta);

	private:
		static Scenes* Instance;
		std::unique_ptr<Scene> scene{ nullptr };
		std::unique_ptr<Scene> nextScene{ nullptr };
	};

}