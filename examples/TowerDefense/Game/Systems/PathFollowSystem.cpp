#include "PathFollowSystem.hpp"
#include "../Components/PathFollowerComponent.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>

PathFollowSystem::PathFollowSystem(std::shared_ptr<Level> level) : level(level) {}
void PathFollowSystem::Update(std::vector<zae::Entity*> entities)
{
	for (const auto& e : entities)
	{
		auto p = e->GetComponent<PathFollowerComponent>();
		auto t = e->GetComponent<zae::Transform>();
		if (p == nullptr || t == nullptr)
		{
			continue;
		}
	}
}

void PathFollowSystem::Update()
{

}