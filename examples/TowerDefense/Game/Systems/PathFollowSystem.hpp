#pragma once

#include <vector>
#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include "../Data/Level.hpp"

class PathFollowSystem : public zae::System
{
public:
	PathFollowSystem(std::shared_ptr<Level> level);
	~PathFollowSystem() override = default;

	void Update(std::vector<zae::Entity*> entities);
	void Update() override;

private:
	std::shared_ptr<Level> level;
};