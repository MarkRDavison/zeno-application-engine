#pragma once

#include "../Game/Data/Level.hpp"
#include "../Game/Processes/CreepSpawnProcess.hpp"
#include <zae/Engine/Scene/Scene.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Game/Camera3DPerspective.hpp>

class GameScene : public zae::Scene
{
public:
	GameScene();

protected:

	void Start() override;
	void Update(float delta) override;

private:
	zae::Camera3DPerspective camera;
	float rotation = 0.0f;
	float distance = 10.0f;
	float height = 2.5f;
	std::shared_ptr<Level> level;
	std::shared_ptr< CreepSpawnProcess> creepSpawn;
};