#include "MessageBus.hpp"

MessageBus* MessageBus::Instance = nullptr;

zae::Signal<CreepReachedEndMessage> MessageBus::OnCreepReachedEndMessage = {};
zae::Signal<CreepSpawnedMessage> MessageBus::OnCreepSpawnedMessage = {};
zae::Signal<RoundCompleteMessage> MessageBus::OnRoundCompleteMessage = {};