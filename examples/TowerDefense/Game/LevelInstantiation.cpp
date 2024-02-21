#include "LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"
#include <zae/Core/Log.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include "Components/PathFollowerComponent.hpp"
#include "Components/CreepComponent.hpp"
#include "Prefabs/TowerPrefabs.hpp"


std::shared_ptr<Level> LevelInstantiation::CreateExampleLevel(zae::EntityHolder& entities)
{
	auto debugStart = zae::Time::Now();
	zae::Log::Info("LevelInstantiation::CreateExampleLevel - begin", '\n');

	auto level = std::make_shared<Level>(); 
	std::vector<Tile>& tiles = level->tiles;

	tiles.emplace_back(Tile{ .position = {-2, +2}, .mesh = "FLAT_TERRAIN_GREEN_END_ROUND_SPAWN", .rotation = 270.0f });
	tiles.emplace_back(Tile{ .position = {-1, +2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+0, +2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+1, +2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+2, +2}, .mesh = "FLAT_TERRAIN_GREEN_CORNER_SQUARE", .rotation = 180.0f });

	tiles.emplace_back(Tile{ .position = {-2, +1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {-1, +1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+0, +1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+1, +1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+2, +1}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT" });

	tiles.emplace_back(Tile{ .position = {-2, +0}, .mesh = "FLAT_TERRAIN_GREEN_CORNER_SQUARE", .rotation = 270.0f });
	tiles.emplace_back(Tile{ .position = {-1, +0}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+0, +0}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+1, +0}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+2, +0}, .mesh = "FLAT_TERRAIN_GREEN_CORNER_SQUARE", .rotation = 90.0f });

	tiles.emplace_back(Tile{ .position = {-2, -1}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT" });
	tiles.emplace_back(Tile{ .position = {-1, -1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+0, -1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+1, -1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+2, -1}, .mesh = "FLAT_TERRAIN_GREEN" });

	tiles.emplace_back(Tile{ .position = {-2, -2}, .mesh = "FLAT_TERRAIN_GREEN_CORNER_SQUARE" });
	tiles.emplace_back(Tile{ .position = {-1, -2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+0, -2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+1, -2}, .mesh = "FLAT_TERRAIN_GREEN_STRAIGHT", .rotation = 90.0f });
	tiles.emplace_back(Tile{ .position = {+2, -2}, .mesh = "FLAT_TERRAIN_GREEN_END_SPAWN", .rotation = 90.0f });

	// TODO: multiple paths, or dynamic pathfinding??????
	//	-	Might have multiple paths per spawnpoint, when spawning random or hard coded etc based on travel/movement type
	level->path = 
	{
		{-2, +2}, {-1, +2}, {+0, +2}, {+1, +2}, {+2, +2},
		                                        {+2, +1}, 
		{+2, +0}, {+1, +0}, {+0, +0}, {-1, +0}, {-2, +0},
		{-2, -1}, 
		{-2, -2}, {-1, -2}, {+0, -2}, {+1, -2}, {+2, -2}
	};

	level->round = Round
	{
		.waves = {
			Wave{
				.amount = 20,
				.remaining = 20,
				.type = "ENEMY_UFO_GREEN",
				.spawn = "THE_SPAWN",
				.interval = 0.5f,
				.delay = 2.5f,
				.elapsed = 0.0f
			}
		}
	};

	for (const auto& t : tiles) {
		auto e = entities.CreateEntity();
		e->AddTag("TERRAIN");
		e->SetName("x=" + std::to_string(t.position.x) + ",z=" + std::to_string(t.position.y));
		auto transform = e->AddComponent<zae::Transform>();
		transform->SetLocalPosition({ (float)t.position.x, 0.0f, (float)t.position.y });
		if (t.rotation != 0.0f)
		{
			transform->SetLocalRotation({ 0.0f, -zae::Math::Radians(t.rotation), 0.0f});
		}
		auto mesh = e->AddComponent<zae::MeshComponent>();
		mesh->SetMesh(MeshHelper::LocateMesh(t.mesh));
	}

	// TODO: Wasted targets?? add some randomness to values???
	TowerPrefabs::SpawnTestTower(entities, { +1,-1 });
	TowerPrefabs::SpawnTestTower(entities, { -1,+1 });

	zae::Log::Info("LevelInstantiation::CreateExampleLevel - end in ", (zae::Time::Now() - debugStart).AsMilliseconds<float>(), "ms", '\n');

	return level;
}