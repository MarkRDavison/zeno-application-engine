#include "TowerFiringSystem.hpp"
#include <cassert>

#include "../Components/CreepComponent.hpp"
#include <zae/Core/Log.hpp>
#include <zae/Engine/Engine.hpp>
#include "../Prefabs/ProjectilePrefabs.hpp"


TowerFiringSystem::TowerFiringSystem(
	zae::EntityHolder* entities
) : zae::ComponentSystem<TowerWeaponComponent, zae::Transform>(entities)
{
	SetQueryTag("TOWER");
}

void TowerFiringSystem::Update(std::vector<zae::Entity*> entities)
{
	const float delta = zae::Engine::Get()->GetDelta().AsSeconds<float>();

	for (const auto& towerEntity: entities)
	{
		auto twc = towerEntity->GetComponent<TowerWeaponComponent>();

		twc->elapsed += delta;
		assert(twc->elapsed > 0.0f); // overflow detection???

		if (twc->elapsed < twc->firingInterval)
		{
			// Not ready to fire.
			continue;
		}

		if (twc->target == nullptr || twc->target->IsRemoved())
		{
			// No target.
			twc->target = nullptr;
			continue;
		}

		auto tt = towerEntity->GetComponent<zae::Transform>();

		ProjectilePrefabs::SpawnTestProjectile(*this->entities, tt->GetLocalPosition(), twc->target);

		twc->elapsed = 0.0f;
	}
}