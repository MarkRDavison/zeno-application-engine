#include "GameScene.hpp"
#include "../Game/LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"
#include "../Game/Systems/PathFollowSystem.hpp"
#include <zae/Game/InputActionManager.hpp>

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

	level = LevelInstantiation::CreateExampleLevel(entities);

	systems.Add<PathFollowSystem>(std::make_unique<PathFollowSystem>(level));
}

void GameScene::Update(float delta)
{
	auto iam = zae::InputActionManager::Get();

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

	const float ROTATE_SPEED = 90.0f;

	rotation += cameraRotate * delta * ROTATE_SPEED;

	const float distance = 10.0f;

	const float x = std::sinf(zae::Math::Radians(rotation)) * distance;
	const float z = std::cosf(zae::Math::Radians(rotation)) * distance;

	camera.SetRotation({ 0.0f, -zae::Math::Radians(rotation) , 0.0f });
	camera.SetPosition({ x, 2.5f, z });

	const auto& entities = QueryAll();

	systems.Get<PathFollowSystem>()->Update(entities);
	// TODO: Better system of this.  Maybe register system against the tags it wants to update????

	iam->UpdateInputCache();
}