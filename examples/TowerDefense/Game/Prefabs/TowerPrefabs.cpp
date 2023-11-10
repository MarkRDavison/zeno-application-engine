#include "TowerPrefabs.hpp"
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include "../Components/TowerWeaponComponent.hpp"
#include "../../Graphics/MeshHelper.hpp"

zae::Entity* TowerPrefabs::SpawnTestTower(zae::EntityHolder& entities, const zae::Vector2i& tile)
{
	{
		auto e = entities.CreateEntity();
		e->AddTag("WEAPON_CANNON_#?");
		e->SetName("WEAPON_CANNON_#?_TOWER_A");
		auto transform = e->AddComponent<zae::Transform>();
		transform->SetLocalPosition({ static_cast<float>(tile.x), 0.2f, static_cast<float>(tile.y) });
		auto mesh = e->AddComponent<zae::MeshComponent>();
		mesh->SetMesh(MeshHelper::LocateMesh("TOWER_SQUARE_BOTTOM_A"));
	}
	{
		auto e = entities.CreateEntity();
		e->AddTag("TOWER");
		e->AddTag("WEAPON_CANNON_#?");
		e->SetName("WEAPON_CANNON_#?_WEAPON");
		auto transform = e->AddComponent<zae::Transform>();
		transform->SetLocalPosition({ +static_cast<float>(tile.x), 0.7f, static_cast<float>(tile.y) });
		auto mesh = e->AddComponent<zae::MeshComponent>();
		mesh->SetMesh(MeshHelper::LocateMesh("WEAPON_CANNON"));
		auto weapon = e->AddComponent<TowerWeaponComponent>();
		weapon->minRange = 0.5f;
		weapon->maxRange = 4.5f;
		weapon->firingInterval = 2.0f;
		weapon->name = "CANNON";
		weapon->projectileName = "ROCK";

		return e;
	}
}