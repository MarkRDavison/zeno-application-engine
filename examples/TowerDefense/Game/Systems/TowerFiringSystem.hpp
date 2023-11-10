#pragma once

#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include "../Components/TowerWeaponComponent.hpp"

class TowerFiringSystem : public zae::ComponentSystem<TowerWeaponComponent, zae::Transform>
{
public:
	TowerFiringSystem(
		zae::EntityHolder* entities);
	~TowerFiringSystem() override = default;

	void Update(std::vector<zae::Entity*> entities) override;

};