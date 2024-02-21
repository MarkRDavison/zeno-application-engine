#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Core/Utils/Signal.hpp>
#include "CreepReachedEndMessage.hpp"
#include "CreepSpawnedMessage.hpp"
#include "RoundCompleteMessage.hpp"

class MessageBus : zae::NonCopyable
{
public:
	static MessageBus* Get() // TODO: Better scope management
	{
		if (Instance == nullptr)
		{
			Instance = new MessageBus();
		}

		return Instance;
	}

	static void Reset()
	{
		OnCreepReachedEndMessage.clearCallbacks();
		OnCreepSpawnedMessage.clearCallbacks();
		OnRoundCompleteMessage.clearCallbacks();
	}

	static zae::Signal<CreepReachedEndMessage> OnCreepReachedEndMessage;
	static zae::Signal<CreepSpawnedMessage> OnCreepSpawnedMessage;
	static zae::Signal<RoundCompleteMessage> OnRoundCompleteMessage;

private:
	static MessageBus* Instance;
};