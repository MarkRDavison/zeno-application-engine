#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Core/Math/ElapsedTime.hpp>
#include <zae/Core/Time.hpp>
#include <zae/Core/Log.hpp>
#include <zae/Engine/App.hpp>
#include <zae/Core/Utils/Signal.hpp>

namespace zae
{
	class Delta
	{
	public:
		void Update()
		{
			currentFrameTime = Time::Now();
			change = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;
		}

		Time currentFrameTime;
		Time lastFrameTime;
		Time change;
	};

	class ChangePerSecond
	{
	public:
		void Update(const Time& time)
		{
			valueTemp++;

			if (std::floor(time.AsSeconds()) > std::floor(valueTime.AsSeconds()))
			{
				value = valueTemp;
				valueTemp = 0;
			}

			valueTime = time;
		}

		uint32_t valueTemp = 0, value = 0;
		Time valueTime;
	};

	class Engine : NonCopyable
	{
	public:

		static Engine* Get() // TODO: Better scope management
		{
			return Instance;
		}
		
		explicit Engine(std::string argv0);
		~Engine();

		int32_t Run();

		const std::string& GetArgv0() const { return argv0; };

		const Version& GetVersion() const { return version; }

		App* GetApp() const { return app.get(); }

		void SetApp(std::unique_ptr<App>&& app) { this->app = std::move(app); }

		float GetFpsLimit() const { return fpsLimit; }

		void SetFpsLimit(float fpsLimit) { this->fpsLimit = fpsLimit; }

		bool IsRunning() const { return running; }

		const Time& GetDelta() const { return deltaUpdate.change; }

		const Time& GetDeltaRender() const { return deltaRender.change; }

		uint32_t GetUps() const { return ups.value; }

		uint32_t GetFps() const { return fps.value; }

		void RequestClose() { running = false; }

	private:
		static Engine* Instance;
		std::string argv0;
		Version version;

		std::unique_ptr<App> app;

		float fpsLimit;
		bool running;

		Delta deltaUpdate, deltaRender;
		ElapsedTime elapsedUpdate, elapsedRender;
		ChangePerSecond ups, fps;
	};

}