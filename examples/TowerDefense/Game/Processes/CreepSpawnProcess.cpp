#include "CreepSpawnProcess.hpp"
#include "../Messages/MessageBus.hpp"
#include "../Prefabs/CreepPrefabs.hpp"
#include <zae/Core/Log.hpp>
#include <zae/Engine/Engine.hpp>

CreepSpawnProcess::CreepSpawnProcess(
	std::shared_ptr<Level> level, 
	zae::EntityHolder& entities
) : 
	level(level),
	entities(entities)
{
	MessageBus::Get()->OnCreepReachedEndMessage.registerCallback(
		[&](CreepReachedEndMessage message) -> void
		{
			this->recheckCreeps = true;
			zae::Log::Info("Creep '", message.type, "' reached the end.\n");
		});
}

void CreepSpawnProcess::Update()
{
	if (!level->round.has_value())
	{
		return;
	}

	if (level->round->allSpawned)
	{
		// TODO: Check if all the spawned ones have been killed/reached the end, 
		// this is bad and wont work if you have multiple round going at once
		if (!recheckCreeps)
		{
			return;
		}

		recheckCreeps = false;
		if (!entities.QueryByTag("CREEP").empty())
		{
			return;
		}

		level->round = {};
		MessageBus::Get()->OnRoundCompleteMessage(RoundCompleteMessage
			{
				.spawning = false,
				.creeping = true
			});
		return;
	}

	const float delta = zae::Engine::Get()->GetDelta().AsSeconds<float>();

	bool complete = true;

	for (auto& wave : level->round->waves)
	{
		float waveDelta = delta;
		if (wave.remaining > 0)
		{
			complete = false;
			
			if (wave.delay > 0.0f)
			{
				wave.delay -= waveDelta;
				if (wave.delay < 0.0f)
				{
					wave.delay = 0.0f;
					waveDelta = -wave.delay;
					wave.elapsed = wave.interval;
				}
			}

			if (waveDelta <= 0.0f || wave.delay > 0.0f)
			{
				continue;
			}

			wave.elapsed -= waveDelta;
			if (wave.elapsed <= 0.0f)
			{
				SpawnCreep(wave.type, wave.spawn);
				wave.elapsed += wave.interval;
				wave.remaining -= 1;
			}
		}
	}

	if (complete)
	{
		level->round->allSpawned = true;
		MessageBus::Get()->OnRoundCompleteMessage(RoundCompleteMessage
			{
				.spawning = true,
				.creeping = false
			});
	}
}

void CreepSpawnProcess::SpawnCreep(const std::string& type, const std::string& spawn)
{
	auto e = CreepPrefabs::SpawnTestCreep(entities);
	MessageBus::Get()->OnCreepSpawnedMessage(CreepSpawnedMessage
		{
			.entity = e,
			.type = type,
			.spawn = spawn
		});
}