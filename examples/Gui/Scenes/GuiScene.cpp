#include "GuiScene.hpp"

#include <zae/Engine/Uis/Uis.hpp>

GuiScene::GuiScene(zae::Camera* camera) : zae::Scene(camera)
{
	zae::Uis::Get()->GetCanvas().AddChild(&logo);
}

void GuiScene::Start()
{

}

void GuiScene::Update(float delta)
{

}
