#pragma once

#include <vector>
#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include "../Components/PathFollowerComponent.hpp"
#include "../Components/CreepComponent.hpp"
#include "../Data/Level.hpp"

class PathFollowSystem : public zae::ComponentSystem<CreepComponent, PathFollowerComponent, zae::Transform>
{
public:
	PathFollowSystem(
		zae::EntityHolder *entities,
		std::shared_ptr<Level> level);
	~PathFollowSystem() override = default;

	void Update(std::vector<zae::Entity*> entities);

private:
	std::shared_ptr<Level> level;
};