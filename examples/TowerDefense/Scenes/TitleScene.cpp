#include "TitleScene.hpp"
#include "../Systems/TitleUiSystem.hpp"

#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/TextComponent.hpp>
#include <zae/Game/InputActionManager.hpp>
#include "../Components/UiTextComponent.hpp"

TitleScene::TitleScene(zae::Camera* camera) : zae::Scene(camera)
{

}

void SetTextInfo(
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
	t->SetLocalPosition({position.x, -position.y, position.z});

	auto ui = e->AddComponent<UiTextComponent>();
	ui->canInteract = canInteract;
}

void TitleScene::Start()
{
	// GetOrAdd is bad for font, its T::Create(path, load) method has extra parameters


	zae::Resources::Get()->Add(
		zae::ResourceNode(
			"TITLE_FONT",
			"fonts/SegoeUi.ttf"),
		std::make_shared<zae::Font>("fonts/SegoeUi.ttf"));

	{
		auto e = entities.CreateEntity();
		e->SetName("TITLE");
		SetTextInfo(e, "TITLE_FONT", "Tower Defense!!!", 64, {8.0f, 8.0f, 0.0f}, false);
	}
	{
		auto e = entities.CreateEntity();
		e->SetName("START");
		SetTextInfo(e, "TITLE_FONT", "Start", 36, { 8.0f, 32.0f + 72.0f * 1.0f, 0.0f }, true);
	}
	{
		auto e = entities.CreateEntity();
		e->SetName("OPTIONS");
		SetTextInfo(e, "TITLE_FONT", "Options", 36, { 8.0f, 32.0f + 72.0f * 2.0f, 0.0f }, true);
	}
	{
		auto e = entities.CreateEntity();
		e->SetName("QUIT");
		SetTextInfo(e, "TITLE_FONT", "Quit", 36, { 8.0f, 32.0f + 72.0f * 3.0f, 0.0f }, true);
	}

	systems.Add<TitleUiSystem>(std::make_unique<TitleUiSystem>());
	auto titleUiSystem = systems.Get<TitleUiSystem>();
	titleUiSystem->onTitleItemClicked.registerCallback([&](std::string str) -> void
		{
			if (str == "START")
			{
				zae::Log::Warning("Starting game.", '\n');
			}
			else if (str == "OPTIONS")
			{
				zae::Log::Warning("Transitioning to options.", '\n');
			}
			else if (str == "QUIT")
			{
				zae::Engine::Get()->RequestClose();
			}
			else
			{
				zae::Log::Warning("Unhandled menu item ", std::quoted(str), " clicked.", '\n');
			}
		});
}

void TitleScene::Update(float delta)
{
	auto iam = zae::InputActionManager::Get();

	auto titleUiSystem = systems.Get<TitleUiSystem>();

	titleUiSystem->Update(QueryAll());

	iam->UpdateInputCache();
}