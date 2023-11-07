#include "LevelInstantiation.hpp"
#include "../Graphics/MeshHelper.hpp"
#include <zae/Core/Log.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include "../Data/Tile.hpp"


void LevelInstantiation::CreateExampleLevel(zae::EntityHolder& entities)
{
	auto debugStart = zae::Time::Now();
	zae::Log::Info("LevelInstantiation::CreateExampleLevel - begin", '\n');

	std::vector<Tile> tiles;
	tiles.emplace_back(Tile{ .position = {-2, +0}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {-1, +0}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+0, +0}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+1, +0}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+2, +0}, .mesh = "FLAT_TERRAIN_GREEN" });

	tiles.emplace_back(Tile{ .position = {-2, -1}, .mesh = "FLAT_TERRAIN_GREEN_TREE4" });
	tiles.emplace_back(Tile{ .position = {-1, -1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+0, -1}, .mesh = "FLAT_TERRAIN_GREEN_ROCK" });
	tiles.emplace_back(Tile{ .position = {+1, -1}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+2, -1}, .mesh = "FLAT_TERRAIN_GREEN" });

	tiles.emplace_back(Tile{ .position = {-2, -2}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {-1, -2}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+0, -2}, .mesh = "FLAT_TERRAIN_GREEN" });
	tiles.emplace_back(Tile{ .position = {+1, -2}, .mesh = "FLAT_TERRAIN_GREEN_HILL" });
	tiles.emplace_back(Tile{ .position = {+2, -2}, .mesh = "FLAT_TERRAIN_GREEN_ROCK" });

	for (const auto& t : tiles) {
		auto e = entities.CreateEntity();
		// TODO: give entities a tag, query by tag etc
		e->SetName("x=" + std::to_string(t.position.x) + ",z=" + std::to_string(t.position.y));
		auto transform = e->AddComponent<zae::Transform>();
		transform->SetLocalPosition({ (float)t.position.x, 0.0f, (float)t.position.y });
		auto mesh = e->AddComponent<zae::MeshComponent>();
		mesh->SetMesh(MeshHelper::LocateMesh(t.mesh));
	}

	zae::Log::Info("LevelInstantiation::CreateExampleLevel - end in ", (zae::Time::Now() - debugStart).AsMilliseconds<float>(), "ms", '\n');
}