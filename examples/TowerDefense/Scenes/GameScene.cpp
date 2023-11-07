#include "GameScene.hpp"
#include "../Game/LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"

GameScene::GameScene() : zae::Scene(&camera)
{
	camera.SetPosition({ 0.0f, 1.5f, 5.0f });
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

	LevelInstantiation::CreateExampleLevel(entities);
}

void GameScene::Update(float delta)
{
}