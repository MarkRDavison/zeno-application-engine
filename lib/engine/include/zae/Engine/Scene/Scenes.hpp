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

		void SetScene(Scene* scene);
		Scene* GetScene();
		void Update(float delta);

	private:
		static Scenes* Instance;
		Scene* scene{ nullptr };
	};

}