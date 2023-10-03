#pragma once

#include <zae/Engine/Scene/Scene.hpp>

class Game3DScene : public zae::Scene
{
public:
	Game3DScene(zae::Camera* camera);

protected:
	void Start() override;
	void Update(float delta) override;
};