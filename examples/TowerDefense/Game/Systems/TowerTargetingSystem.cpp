#include "TowerTargetingSystem.hpp"

#include "../Components/CreepComponent.hpp"
#include <zae/Core/Log.hpp>


TowerTargetingSystem::TowerTargetingSystem(
	zae::EntityHolder* entities
) : zae::ComponentSystem<TowerWeaponComponent, zae::Transform>(entities)
{
	SetQueryTag("TOWER");
}

bool InRange(const TowerWeaponComponent *twc, zae::Transform *towerTransform, const zae::Transform *targetTransform)
{
	auto towerPosition = towerTransform->GetLocalPosition();
	auto creepPosition = targetTransform->GetLocalPosition();

	const auto towerHorizontalPosition = zae::Vector2f(towerPosition.x, towerPosition.z);
	const auto creepHorizontalPosition = zae::Vector2f(creepPosition.x, creepPosition.z);

	const auto distance = towerHorizontalPosition.Distance(creepHorizontalPosition);

	bool inRange = twc->minRange <= distance && distance <= twc->maxRange;

	if (inRange)
	{
		const auto offset = creepHorizontalPosition - towerHorizontalPosition;

		// TODO: PI/2 rotation offset is because model rotation is off
		towerTransform->SetLocalRotation({ 0.0f, zae::Math::WrapRadians(zae::Math::PI<float> / 2.0f - offset.Angle()), 0.0f });
	}

	return inRange;
}


void TowerTargetingSystem::Update(std::vector<zae::Entity*> entities)
{
	const auto& creeps = this->entities->QueryByTag("CREEP");

	for (const auto& towerEntity : entities)
	{
		auto twc = towerEntity->GetComponent<TowerWeaponComponent>();
		auto t = towerEntity->GetComponent<zae::Transform>();

		if (twc->target != nullptr)
		{
			if (!twc->target->IsRemoved())
			{
				auto currentTargetTransform = twc->target->GetComponent<zae::Transform>();

				if (currentTargetTransform != nullptr)
				{
					if (!InRange(twc, t, currentTargetTransform))
					{
						twc->target = nullptr;
					}
					else
					{
						// Target still valid, carry on
						continue;
					}
				}
			}
		}

		twc->target = nullptr;
		// Need to find a target, either didn't have one or the old one wandered out of range

		for (const auto& creepEntity : creeps)
		{
			auto potentialTargetTransform = creepEntity->GetComponent<zae::Transform>();
			if (potentialTargetTransform != nullptr)
			{
				if (InRange(twc, t, potentialTargetTransform))
				{
					twc->target = creepEntity;
					continue;
				}
			}
		}
	}
}