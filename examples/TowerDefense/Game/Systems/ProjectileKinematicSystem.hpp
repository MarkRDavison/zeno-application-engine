#pragma once

#include <vector>
#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include "../Components/ProjectileComponent.hpp"

class ProjectileKinematicSystem : public zae::ComponentSystem<ProjectileComponent, zae::Transform>
{
public:
	ProjectileKinematicSystem(
		zae::EntityHolder* entities);
	~ProjectileKinematicSystem() override = default;

	void Update(std::vector<zae::Entity*> entities);

};