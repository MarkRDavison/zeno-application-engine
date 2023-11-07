#include "LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"
#include <zae/Core/Log.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>


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

	level->path = 
	{
		{-2, +2}, {-1, +2}, {+0, +2}, {+1, +2}, {+2, +2},
		                                        {+2, +1}, 
		{+2, +0}, {+1, +0}, {+0, +0}, {-1, +0}, {-2, +0},
		{-2, -1}, 
		{-2, -2}, {-1, -2}, {+0, -2}, {+1, -2}, {+2, -2}
	};

	for (const auto& t : tiles) {
		auto e = entities.CreateEntity();
		// TODO: give entities a tag, query by tag etc
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

	//{
	//	auto e = entities.CreateEntity();
	//	e->SetName("ENEMENY_UFO_GREEN_#1");
	//	auto transform = e->AddComponent<zae::Transform>();
	//	transform->SetLocalPosition({ -2.0f, 0.5f, +2.0f });
	//	transform->SetLocalScale({ 0.5f, 0.5f, 0.5f });
	//	auto mesh = e->AddComponent<zae::MeshComponent>();
	//	mesh->SetMesh(MeshHelper::LocateMesh("ENEMY_UFO_GREEN"));
	//}

	zae::Log::Info("LevelInstantiation::CreateExampleLevel - end in ", (zae::Time::Now() - debugStart).AsMilliseconds<float>(), "ms", '\n');

	return level;
}