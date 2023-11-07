#pragma once

#include <zae/Engine/Scene/Scene.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Game/Camera3DOrthographic.hpp>

class TitleScene : public zae::Scene
{
public:
	TitleScene();

protected:
	void Start() override;
	void Update(float delta) override;

private:
	zae::Camera3DOrthographic camera;
};