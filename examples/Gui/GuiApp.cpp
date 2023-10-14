#include "GuiApp.hpp"
#include "GuiRenderer.hpp"
#include "Scenes/GuiScene.hpp"

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Scene/Scenes.hpp>
#include <zae/Engine/Uis/Uis.hpp>
#include <zae/Game/Camera3DOrthographic.hpp>
#include <zae/Game/InputActionManager.hpp>

GuiApp::GuiApp() : zae::App("Zeno Application Engine - Gui Example")
{

}
GuiApp::~GuiApp()
{
	zae::Files::Get()->ClearSearchPath();
}

void GuiApp::Start()
{
	// TODO: Replace with initialize methods
	zae::Windows::Get();
	zae::Files::Get();
	zae::Graphics::Get();
	zae::Resources::Get();
	zae::InputActionManager::Get();
	zae::Uis::Get();
	// Windows
	// Files
	// Graphics
	// Resources
	// Inputs
	// Scenes
	// Timers

	zae::Windows::Get()->AddWindow();

	zae::Windows::Get()->GetWindow(0)->OnClose().registerCallback([]() { zae::Engine::Get()->RequestClose(); });
	zae::Windows::Get()->GetWindow(0)->SetTitle(zae::App::GetName());

	zae::Graphics::Get()->SetRenderer(std::make_unique<GuiRenderer>());

	auto iam = zae::InputActionManager::Get();
	{
		auto action = zae::InputActionType{
			.name = "SPACE",
			.key = zae::Key::Space,
			.actionType = zae::ActionType::KEY
		};
		iam->RegisterInputActionType(action);
	}

	zae::Scenes::Get()->SetScene(new GuiScene(new zae::Camera3DOrthographic()));
}

void GuiApp::Update()
{
	auto iam = zae::InputActionManager::Get();
	if (iam->IsActionInvoked("SPACE"))
	{
		zae::Log::Info(std::quoted("SPACE"), " invoked.\n");
	}

	iam->UpdateInputCache();
}