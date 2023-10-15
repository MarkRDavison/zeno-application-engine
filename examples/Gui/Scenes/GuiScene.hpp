#pragma once

#include <zae/Engine/Scene/Scene.hpp>

#include "../Ui/Panels.hpp"

#include <zae/Engine/Uis/Objects/UiStartLogo.hpp>

class GuiScene : public zae::Scene
{
public:
	GuiScene(zae::Camera* camera);

protected:
	void Start() override;
	void Update(float delta) override;

private:
	Panels panels;
	zae::UiStartLogo logo;
};