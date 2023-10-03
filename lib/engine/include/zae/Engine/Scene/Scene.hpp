#pragma once

#include <zae/Engine/Scene/Camera.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>
#include <zae/Engine/Scene/Entity/SystemHolder.hpp>

namespace zae
{

	class Scene
	{
	public:
		Scene(Camera* camera) : camera(camera)
		{

		}

		void UpdateScene(float delta)
		{
			if (!active) 
			{ 
				return; 
			}

			if (!started)
			{
				Start();
				started = true;
			}

			Update(delta);

			camera->Update(delta);
		}

		bool IsActive() const { return this->active; }
		void SetActive(bool active) { this->active = active; }

		std::vector<Entity*> QueryAll() { return entities.QueryAll(); }

		const Camera* GetCamera() const { return camera; }

	protected:
		virtual void Update(float delta) = 0;
		virtual void Start() {}

	protected:
		bool started{ false };
		bool active{ true };

		Camera* camera;

		SystemHolder systems;

		EntityHolder entities;
	};

}