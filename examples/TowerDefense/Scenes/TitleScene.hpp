#pragma once

#include <zae/Engine/Scene/Scene.hpp>
#include <zae/Engine/Resources/Resources.hpp>

class TitleScene : public zae::Scene
{
public:
	TitleScene(zae::Camera* camera);

protected:
	void Start() override;
	void Update(float delta) override;

};