#include "TowerDefenseApp.hpp"
#include "Scenes/TitleScene.hpp"
#include "Renderers/TowerDefenseRenderer.hpp"
#include "Renderers/TitleSceneRenderer.hpp"

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Scene/Scenes.hpp>
#include <zae/Game/InputActionManager.hpp>
#include <zae/Game/Camera3DOrthographic.hpp>
#include <zae/Game/Camera3DPerspective.hpp>
#include "Scenes/SceneTransitions.hpp"

TowerDefenseApp::TowerDefenseApp() : zae::App("Zeno Application Engine - TowerDefense Example")
{

}
TowerDefenseApp::~TowerDefenseApp()
{
	zae::Scenes::Get()->SetScene(nullptr);
	zae::Files::Get()->ClearSearchPath();
}

void TowerDefenseApp::Start()
{
	// TODO: Replace with initialize methods
	zae::Windows::Get();
	zae::Files::Get();
	zae::Graphics::Get();
	zae::Resources::Get();
	zae::InputActionManager::Get();
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

	auto iam = zae::InputActionManager::Get();
	{
		auto action = zae::InputActionType{
			.name = "SPACE",
			.key = zae::Key::Space,
			.actionType = zae::ActionType::KEY
		};
		iam->RegisterInputActionType(action);
	}
	{
		auto action = zae::InputActionType{
			.name = "CLICK",
			.mouseButton = zae::MouseButton::Left,
			.actionType = zae::ActionType::MOUSE_BUTTON
		};
		iam->RegisterInputActionType(action);
	}

	SceneTransitions::SetTitleScene();
}

void TowerDefenseApp::Update()
{
}