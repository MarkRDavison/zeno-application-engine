#include "GameScene.hpp"
#include "../Game/LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"
#include <zae/Game/InputActionManager.hpp>
#include "../Game/Systems/PathFollowSystem.hpp"
#include "../Game/Systems/TowerTargetingSystem.hpp"
#include "../Game/Systems/TowerFiringSystem.hpp"
#include "../Game/Systems/ProjectileKinematicSystem.hpp"

GameScene::GameScene() : zae::Scene(&camera)
{
	camera.SetPosition({ 0.0f, 2.5f, 10.0f });
}

void GameScene::Start()
{
	// TODO: Need a better place to register default resources.  Make sure they aren't auto removed
	zae::Resources::Get()->Add(
		zae::ResourceNode("DEFAULT", "textures/default.png"), 
		zae::Image2d::Create("textures/default.png"));

	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN", "models/tile.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_DIRT", "models/tile_dirt.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_ROCK", "models/tile_rock.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_HILL", "models/tile_hill.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_TREE", "models/tile_tree.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_TREE2", "models/tile_treeDouble.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_TREE4", "models/tile_treeQuad.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_SPAWN", "models/tile_spawn.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_STRAIGHT", "models/tile_straight.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_END_SPAWN", "models/tile_endSpawn.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_CORNER_SQUARE", "models/tile_cornerSquare.obj");
	MeshHelper::RegisterMesh("FLAT_TERRAIN_GREEN_END_ROUND_SPAWN", "models/tile_endRoundSpawn.obj");
	MeshHelper::RegisterMesh("ENEMY_UFO_GREEN", "models/enemy_ufoGreen.obj");
	MeshHelper::RegisterMesh("WEAPON_BALLISTA", "models/weapon_ballista.obj");
	MeshHelper::RegisterMesh("WEAPON_CANNON", "models/weapon_cannon.obj");
	MeshHelper::RegisterMesh("TOWER_ROUND_BOTTOM_A", "models/towerRound_bottomA.obj");
	MeshHelper::RegisterMesh("TOWER_ROUND_BOTTOM_B", "models/towerRound_bottomB.obj");
	MeshHelper::RegisterMesh("TOWER_ROUND_BOTTOM_C", "models/towerRound_bottomC.obj");
	MeshHelper::RegisterMesh("TOWER_SQUARE_BOTTOM_A", "models/towerSquare_bottomA.obj");
	MeshHelper::RegisterMesh("TOWER_SQUARE_BOTTOM_B", "models/towerSquare_bottomB.obj");
	MeshHelper::RegisterMesh("TOWER_SQUARE_BOTTOM_C", "models/towerSquare_bottomC.obj");
	MeshHelper::RegisterMesh("ROCK", "models/rock.obj");

	level = LevelInstantiation::CreateExampleLevel(entities);

	creepSpawn = std::make_shared<CreepSpawnProcess>(level, entities);

	systems.Add<PathFollowSystem>(std::make_unique<PathFollowSystem>(&entities, level));
	systems.Add<TowerTargetingSystem>(std::make_unique<TowerTargetingSystem>(&entities));
	systems.Add<TowerFiringSystem>(std::make_unique<TowerFiringSystem>(&entities));
	systems.Add<ProjectileKinematicSystem>(std::make_unique<ProjectileKinematicSystem>(&entities));
}

void GameScene::Update(float delta)
{
	const float ROTATE_SPEED = 90.0f;
	const float ZOOM_SPEED = 10.0f;
	const float HEIGHT_SPEED = 2.5f;

	auto iam = zae::InputActionManager::Get();

	{	// Camera stuff
		const auto& window = zae::Windows::Get()->GetWindow(0);
		float cameraRotate = 0.0f;
		if (window->GetKey(zae::Key::A) == zae::InputAction::Press)
		{
			cameraRotate -= 1.0f;
		}
		if (window->GetKey(zae::Key::D) == zae::InputAction::Press)
		{
			cameraRotate += 1.0f;
		}
		if (window->GetKey(zae::Key::W) == zae::InputAction::Press)
		{
			distance -= ZOOM_SPEED * delta;
			distance = std::max(distance, 7.5f);
		}
		if (window->GetKey(zae::Key::S) == zae::InputAction::Press)
		{
			distance += ZOOM_SPEED * delta;
		}
		if (window->GetKey(zae::Key::Q) == zae::InputAction::Press)
		{
			height += HEIGHT_SPEED * delta;
		}
		if (window->GetKey(zae::Key::E) == zae::InputAction::Press)
		{
			height -= HEIGHT_SPEED * delta;
			height = std::max(height, 0.5f);
		}

		rotation += cameraRotate * delta * ROTATE_SPEED;

		const float x = std::sinf(zae::Math::Radians(rotation)) * distance;
		const float z = std::cosf(zae::Math::Radians(rotation)) * distance;

		camera.SetRotation({ 0.0f, -zae::Math::Radians(rotation) , 0.0f });
		camera.SetPosition({ x, height, z });
	}

	systems.ForEach([](auto typeId, auto sytem) { sytem->Update(); });

	creepSpawn->Update();
	
	iam->UpdateInputCache();
}