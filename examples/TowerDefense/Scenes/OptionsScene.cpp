#include "OptionsScene.hpp"
#include "../Components/UiTextComponent.hpp"
#include <zae/Engine/Scene/Entity/Components/TextComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>

OptionsScene::OptionsScene() : zae::Scene(&camera)
{

}

void SetOptionsTextInfo(
	zae::Entity* e,
	const std::string& font,
	const std::string& string,
	unsigned size,
	zae::Vector3f position,
	bool canInteract)
{
	auto text = e->AddComponent<zae::TextComponent>();

	text->SetFont(zae::Resources::Get()->Find<zae::Font>(zae::ResourceNode(font)));
	text->SetSize(size);
	text->SetText(string);
	text->SetInternalColour(zae::Colour::Black);
	text->SetExternalColour(zae::Colour::White);

	auto t = e->AddComponent<zae::Transform>();
	t->SetLocalPosition({ position.x, -position.y, position.z });

	auto ui = e->AddComponent<UiTextComponent>();
	ui->canInteract = canInteract;
}

void OptionsScene::Start() 
{
	{
		auto e = entities.CreateEntity();
		e->SetName("OPTIONS");
		SetOptionsTextInfo(e, "TITLE_FONT", "Options", 64, { 8.0f, 8.0f, 0.0f }, false);
	}
}

void OptionsScene::Update(float delta)
{
}