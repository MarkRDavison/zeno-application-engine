#pragma once

#include <zae/Engine/Scene/Camera.hpp>

namespace zae
{

	class Scene
	{
	public:
		Scene(Camera* camera) : baseCamera(camera)
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

			baseCamera->Update(delta);
		}

		bool IsActive() const { return this->active; }
		void SetActive(bool active) { this->active = active; }

	protected:
		virtual void Update(float delta) = 0;
		virtual void Start() {}

	protected:
		Camera* baseCamera;
		bool started{ false };
		bool active{ true };
	};

}