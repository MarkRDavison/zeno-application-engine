#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <zae/Core/Time.hpp>
#include <zae/Engine/Engine.hpp>

namespace zae
{
	class Timer
	{
		friend class Timers;
	public:
		Timer(const Time& interval, const std::optional<uint32_t>& repeat) :
			interval(interval),
			next(Time::Now() + interval),
			repeat(repeat)
		{
		}

		const Time& GetInterval() const { return interval; }
		const std::optional<uint32_t>& GetRepeat() const { return repeat; }
		bool IsDestroyed() const { return destroyed; }
		void Destroy() { destroyed = true; }
		Signal<>& OnTick() { return onTick; };

	private:
		Time interval;
		Time next;
		std::optional<uint32_t> repeat;
		bool destroyed = false;
		Signal<> onTick;
	};

	class Timers
	{
		Timers();
	public:
		~Timers();

		static Timers* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new Timers();
			}
			return Instance;
		}

		void Update();

		template<class Instance>
		Timer* Once(Instance* object, std::function<void()>&& function, const Time& delay)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(delay, 1));
			//instance->onTick.connect(object, std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

		template<class Instance>
		Timer* Every(Instance* object, std::function<void()>&& function, const Time& interval)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(interval, std::nullopt));
			//instance->onTick.connect(object, std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

		template<class Instance>
		Timer* Repeat(Instance* object, std::function<void()>&& function, const Time& interval, uint32_t repeat)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(interval, repeat));
			//instance->onTick.connect(object, std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

		Timer* Once(std::function<void()>&& function, const Time& delay)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(delay, 1));
			//instance->onTick.connect(std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

		Timer* Every(std::function<void()>&& function, const Time& interval)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(interval, std::nullopt));
			//instance->onTick.connect(std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

		Timer* Repeat(std::function<void()>&& function, const Time& interval, uint32_t repeat)
		{
			std::unique_lock<std::mutex> lock(mutex);
			auto& instance = timers.emplace_back(std::make_unique<Timer>(interval, repeat));
			//instance->onTick.connect(std::move(function));
			instance->onTick.registerCallback(function);
			condition.notify_all();
			return instance.get();
		}

	private:
		void ThreadRun();

		static Timers* Instance;

		std::vector<std::unique_ptr<Timer>> timers;

		std::atomic_bool stop = false;
		std::thread worker;

		std::mutex mutex;
		std::condition_variable condition;
	};
}
