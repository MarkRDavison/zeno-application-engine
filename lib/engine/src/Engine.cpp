#include <zae/Engine/Engine.hpp>
#include <zae/Core/Config.hpp>

#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Files.hpp>
#include <zae/Engine/Timers.hpp>
#include <zae/Engine/Scene/Scenes.hpp>

#include <exception>

namespace zae
{
	Engine* Engine::Instance = nullptr;

	Engine::Engine(std::string argv0) :
		argv0(std::move(argv0)),
		version{ ZAE_VERSION_MAJOR, ZAE_VERSION_MINOR, ZAE_VERSION_PATCH },
		fpsLimit(-1.0f),
		running(true),
		elapsedUpdate(15.77ms),
		elapsedRender(-1s)
	{
		if (Instance != nullptr) { throw std::exception("Cannot re-created Engine"); }

		Instance = this;

		Log::OpenLog(Time::GetDateTime("Logs/log01.txt"));

#ifdef ZAE_DEBUG
		Log::Out("Version: ", ZAE_VERSION, '\n');
		Log::Out("Git: ", ZAE_COMPILED_COMMIT_HASH, " on ", ZAE_COMPILED_BRANCH, '\n');
		Log::Out("Compiled on: ", ZAE_COMPILED_SYSTEM, " from: ", ZAE_COMPILED_GENERATOR, " with: ", ZAE_COMPILED_COMPILER, "\n\n");
#endif
	}

	Engine::~Engine()
	{
		app = nullptr;

		Log::CloseLog();
	}

	int32_t Engine::Run()
	{
		while (running)
		{

			if (app)
			{
				if (!app->started)
				{
					app->Start();
					app->started = true;
				}

				app->Update();
			}

			elapsedRender.SetInterval(Time::Seconds(1.0f / fpsLimit));

			if (elapsedUpdate.GetElapsed() != 0)
			{
				// Resets the timer.
				ups.Update(Time::Now());

				// TODO: Update non-app components

				// Pre
				Windows::Get()->Update();

				//Inputs::Get()->Update();

				// Normal
				Scenes::Get()->Update(deltaUpdate.change.AsSeconds());

				// Post
				Files::Get()->Update();

				Resources::Get()->Update();

				Timers::Get()->Update();

				// Updates the engines delta.
				deltaUpdate.Update();
			}

			// TODO: Prioritize updates over rendering.
			//if (!Math::AlmostEqual(elapsedUpdate.GetInterval().AsSeconds(), deltaUpdate.change.AsSeconds(), 0.8f)) {
			//	continue;
			//}

			// Renders when needed.
			if (elapsedRender.GetElapsed() != 0)
			{
				// Resets the timer.
				fps.Update(Time::Now());


				// Render
				Graphics::Get()->Update();


				// Updates the render delta, and render time extension.
				deltaRender.Update();
			}
		}

		return EXIT_SUCCESS;
	}
}