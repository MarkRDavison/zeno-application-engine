#include "GameApp.hpp"
#include "GameRenderer.hpp"

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>
#include <zae/Engine/Resources/Resources.hpp>

GameApp::GameApp() : zae::App("Zeno Application Engine - Game Example")
{

}
GameApp::~GameApp()
{
	zae::Files::Get()->ClearSearchPath();
}

void GameApp::Start()
{
	// TODO: Replace with initialize methods
	zae::Windows::Get();
	zae::Files::Get();
	zae::Graphics::Get();
	zae::Resources::Get();
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
}

void GameApp::Update()
{

}