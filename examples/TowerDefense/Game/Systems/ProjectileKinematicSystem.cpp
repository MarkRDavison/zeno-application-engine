#include "ProjectileKinematicSystem.hpp"
#include <zae/Engine/Engine.hpp>


ProjectileKinematicSystem::ProjectileKinematicSystem(
	zae::EntityHolder* entities
) : zae::ComponentSystem<ProjectileComponent, zae::Transform>(entities)
{
	SetQueryTag("PROJECTILE");
}

void ProjectileKinematicSystem::Update(std::vector<zae::Entity*> entities)
{
	const float delta = zae::Engine::Get()->GetDelta().AsSeconds<float>();

	for (const auto projectileEntity : entities)
	{
		auto pc = projectileEntity->GetComponent<ProjectileComponent>();


		if (pc->target == nullptr || pc->target->IsRemoved())
		{
			pc->target = nullptr;
		}
		else
		{
			auto ct = pc->target->GetComponent<zae::Transform>();
			pc->targetLastPosition = ct->GetLocalPosition();
		}

		auto pt = projectileEntity->GetComponent<zae::Transform>();

		auto currentProjectilePosition = pt->GetLocalPosition();

		const auto offset = pc->targetLastPosition - currentProjectilePosition;
		const auto direction = offset.Normalize();
		const auto distance = offset.Length();
		const auto movement = direction * delta * pc->speed;

		if (movement.Length() <= distance)
		{
			pt->SetLocalPosition(currentProjectilePosition + movement);
		}
		else
		{
			pt->SetLocalPosition(pc->targetLastPosition);
			projectileEntity->SetRemoved(true);
			if (pc->target != nullptr)
			{
				// TODO: Handle damaging etc
				pc->target->SetRemoved(true);
			}
		}
	}
}