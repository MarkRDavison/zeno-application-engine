#include "ProjectilePrefabs.hpp"
#include "../../Graphics/MeshHelper.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include "../Components/ProjectileComponent.hpp"

zae::Entity* ProjectilePrefabs::SpawnTestProjectile(zae::EntityHolder& entities, const zae::Vector3f& origin, zae::Entity* target)
{
	auto e = entities.CreateEntity();
	e->AddTag("PROJECTILE");
	auto transform = e->AddComponent<zae::Transform>();
	transform->SetLocalPosition(origin + zae::Vector3f{ 0.0f, 0.25f, 0.0f});
	transform->SetLocalScale({ 0.10f, 0.10f, 0.10f });
	auto mesh = e->AddComponent<zae::MeshComponent>();
	mesh->SetMesh(MeshHelper::LocateMesh("ROCK"));
	auto proj = e->AddComponent<ProjectileComponent>();
	proj->speed = 5.0f;
	proj->target = target;

	return e;
}