#pragma once

#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include "../Components/TowerWeaponComponent.hpp"

class TowerTargetingSystem : public zae::ComponentSystem<TowerWeaponComponent, zae::Transform>
{
public:
	TowerTargetingSystem(
		zae::EntityHolder* entities);
	~TowerTargetingSystem() override = default;

	void Update(std::vector<zae::Entity*> entities) override;

};