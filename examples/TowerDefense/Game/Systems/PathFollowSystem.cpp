#include "PathFollowSystem.hpp"
#include "../Messages/MessageBus.hpp"
#include <zae/Engine/Engine.hpp>

PathFollowSystem::PathFollowSystem(
	zae::EntityHolder* entities,
	std::shared_ptr<Level> level
) : 
	zae::ComponentSystem<CreepComponent, PathFollowerComponent, zae::Transform>(entities),
	level(level) 
{
	SetQueryTag("CREEP");
}

void PathFollowSystem::Update(std::vector<zae::Entity*> entities)
{
	for (const auto& e : entities)
	{
		float delta = zae::Engine::Get()->GetDelta().AsSeconds<float>();

		auto c = e->GetComponent<CreepComponent>();
		auto p = e->GetComponent<PathFollowerComponent>();
		auto t = e->GetComponent<zae::Transform>();

		zae::Vector2f target;

		unsigned nextPathIndex = p->pathIndex + 1;
		if (p->pathIndex == std::numeric_limits<unsigned>::max())
		{
			// Just starting
			target = zae::Vector2f(level->path.begin()->x, level->path.begin()->y);
			nextPathIndex = 1;
		}
		else if (p->pathIndex >= level->path.size())
		{
			MessageBus::Get()->OnCreepReachedEndMessage(CreepReachedEndMessage
				{
					.type = c->type
				});
			e->SetRemoved(true);
			continue;
		}
		else
		{
			target = { level->path[p->pathIndex].x, level->path[p->pathIndex].y };
		}

		zae::Vector2f position = { t->GetLocalPosition().x, t->GetLocalPosition().z };
		
		auto distance = target.Distance<float>(position);

		const float maxMovement = p->speed * delta;

		if (maxMovement >= distance)
		{
			t->SetLocalPosition({ target.x, t->GetLocalPosition().y, target.y });
			p->pathIndex = nextPathIndex;
		}
		else
		{
			const auto direction = (target - position).Normalize();
			auto currentPosition = t->GetLocalPosition();
			t->SetLocalPosition({ currentPosition.x + direction.x * maxMovement, currentPosition.y, currentPosition.z + direction.y * maxMovement});
		}
	}
}