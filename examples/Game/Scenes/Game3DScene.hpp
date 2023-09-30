#pragma once

#include <zae/Game/Scene/Scene3D.hpp>

class Game3DScene : public zae::Scene3D
{
public:
	Game3DScene(zae::Camera3D* camera);

protected:
	void Start() override;
	void Update(float delta) override;
};