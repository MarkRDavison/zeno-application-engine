#pragma once

#include <zae/Engine/Scene/Scene.hpp>

class Game2DScene : public zae::Scene
{
public:
	Game2DScene(zae::Camera* camera);

protected:
	void Start() override;
	void Update(float delta) override;
};