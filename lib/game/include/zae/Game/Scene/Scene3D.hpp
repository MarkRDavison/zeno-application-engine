#pragma once

#include <zae/Engine/Scene/Scene.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>
#include <zae/Engine/Scene/Entity/SystemHolder.hpp>
#include <zae/Game/Camera3D.hpp>

namespace zae
{

	class Scene3D : public Scene
	{
	protected:
		Scene3D(Camera3D* camera);

		void Update(float delta) override;

	protected:
		Camera3D* camera;

		SystemHolder systems;

		EntityHolder entities;
	};

}