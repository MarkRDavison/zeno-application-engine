#include "TextApp.hpp"
#include "TextRenderer.hpp"

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>
#include <zae/Engine/Resources/Resources.hpp>

namespace test
{

	TextApp::TextApp() : zae::App("Zeno Application Engine - Text Example")
	{

	}
	TextApp::~TextApp()
	{
		zae::Files::Get()->ClearSearchPath();
	}

	void TextApp::Start()
	{
		// TODO: Replace with initialize methods
		zae::Windows::Get();
		zae::Files::Get();
		zae::Graphics::Get();
		zae::Resources::Get();

		zae::Windows::Get()->AddWindow();

		zae::Windows::Get()->GetWindow(0)->OnClose().registerCallback([]() { zae::Engine::Get()->RequestClose(); });
		zae::Windows::Get()->GetWindow(0)->SetTitle(zae::App::GetName());
		zae::Graphics::Get()->SetRenderer(std::make_unique<TextRenderer>());
	}

	void TextApp::Update()
	{

	}

}