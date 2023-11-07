#include "GameApp.hpp"
#include "GameRenderer.hpp"
#include "Scenes/Game2DScene.hpp"
#include "Scenes/Game3DScene.hpp"

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Scene/Scenes.hpp>
#include <zae/Game/InputActionManager.hpp>
#include <zae/Game/Camera3DOrthographic.hpp>
#include <zae/Game/Camera3DPerspective.hpp>

GameApp::GameApp() : zae::App("Zeno Application Engine - Game Example")
{

}
GameApp::~GameApp()
{
	zae::Scenes::Get()->SetScene(nullptr);
	zae::Files::Get()->ClearSearchPath();
}

void GameApp::Start()
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

	zae::Graphics::Get()->SetRenderer(std::make_unique<GameRenderer>());

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
	{
		auto action = zae::InputActionType{
			.name = "TOGGLE",
			.key = zae::Key::T,
			.actionType = zae::ActionType::KEY
		};
		iam->RegisterInputActionType(action);
	}
	{
		auto action = zae::InputActionType{
			.name = "TOGGLE_MESH",
			.key = zae::Key::M,
			.actionType = zae::ActionType::KEY
		};
		iam->RegisterInputActionType(action);
	}

	scene2d = true;
	zae::Scenes::Get()->SetScene(std::make_unique<Game2DScene>(new zae::Camera3DOrthographic()));
}

void GameApp::Update()
{
	auto iam = zae::InputActionManager::Get();
	if (iam->IsActionInvoked("SPACE"))
	{
		zae::Log::Info(std::quoted("SPACE"), " invoked.\n");
	}
	if (iam->IsActionInvoked("CLICK"))
	{
		zae::Log::Info(std::quoted("CLICK"), " invoked.\n");
	}
	if (iam->IsActionInvoked("TOGGLE"))
	{
		zae::Log::Info(std::quoted("TOGGLE"), " invoked.\n");
		scene2d = !scene2d;
		if (scene2d)
		{
			const auto& scene = zae::Scenes::Get()->GetScene();
			delete scene->GetCamera();
			zae::Scenes::Get()->SetScene(std::make_unique<Game2DScene>(new zae::Camera3DOrthographic()));
		}
		else
		{
			const auto& scene = zae::Scenes::Get()->GetScene();
			delete scene->GetCamera();
			auto camera = new zae::Camera3DPerspective();
			camera->SetPosition({ 0.0f, 0.5f, 2.5f });
			zae::Scenes::Get()->SetScene(std::make_unique<Game3DScene>(camera));
		}
	}

	iam->UpdateInputCache();
}