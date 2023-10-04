#include <cstdlib>
#include <zae/Engine/Engine.hpp>
#include "TextApp.hpp"

int main(int _argc, char** _argv)
{
	auto engine = std::make_unique<zae::Engine>(_argv[0]);
	engine->SetApp(std::make_unique<TextApp>());

	// Runs the game loop.
	auto exitCode = engine->Run();
	engine = nullptr;

	if (exitCode != EXIT_SUCCESS)
	{
		// Pauses the console.
		std::cout << "Press enter to continue...";
		std::cin.get();
	}

	return exitCode;
}