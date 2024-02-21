#include "CreepPrefabs.hpp"
#include "../Components/CreepComponent.hpp"
#include "../Components/PathFollowerComponent.hpp"
#include "../../Graphics/MeshHelper.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>

zae::Entity* CreepPrefabs::SpawnTestCreep(zae::EntityHolder& entities)
{
	auto e = entities.CreateEntity();
	e->AddTag("CREEP");
	e->SetName("ENEMY_UFO_GREEN_#1");
	auto creep = e->AddComponent<CreepComponent>();
	creep->type = "ENEMY_UFO_GREEN";
	auto transform = e->AddComponent<zae::Transform>();
	transform->SetLocalPosition({ -2.0f, 0.5f, +2.0f });
	transform->SetLocalScale({ 0.5f, 0.5f, 0.5f });
	auto mesh = e->AddComponent<zae::MeshComponent>();
	mesh->SetMesh(MeshHelper::LocateMesh("ENEMY_UFO_GREEN"));
	auto pf = e->AddComponent<PathFollowerComponent>();
	pf->speed = 1.6f;

	return e;
}