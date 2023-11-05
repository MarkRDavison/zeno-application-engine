#include "Game3DScene.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include <zae/Game/InputActionManager.hpp>

Game3DScene::Game3DScene(zae::Camera* camera) : zae::Scene(camera)
{
	mesheResourceNodes.push_back(zae::ResourceNode(
		"TEST_MESH1",
		"models/satelliteDish.obj"));
	mesheResourceNodes.push_back(zae::ResourceNode(
		"TEST_MESH2",
		"models/satelliteDish_detailed.obj"));
	mesheResourceNodes.push_back(zae::ResourceNode(
		"TEST_MESH3",
		"models/satelliteDish_large.obj"));
}

void Game3DScene::Start()
{
	{
		auto e = entities.CreateEntity();
		e->SetName("TEST1");
		auto t = e->AddComponent<zae::Transform>();
		t->SetLocalPosition(zae::Vector3f());
		auto m = e->AddComponent<zae::MeshComponent>();
		m->SetMesh(zae::Resources::Get()->GetOrAdd<zae::Mesh>(mesheResourceNodes[meshResourceNodeIndex]));
	}
}

void Game3DScene::Update(float delta)
{
	if (zae::InputActionManager::Get()->IsActionInvoked("TOGGLE_MESH"))
	{
		meshResourceNodeIndex = (meshResourceNodeIndex + 1) % mesheResourceNodes.size();

		auto e = entities.GetEntity("TEST1");
		auto m = e->GetComponent<zae::MeshComponent>(); 
		m->SetMesh(zae::Resources::Get()->GetOrAdd<zae::Mesh>(mesheResourceNodes[meshResourceNodeIndex]));
	}
}
