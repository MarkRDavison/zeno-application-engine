#include "Game3DScene.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>

Game3DScene::Game3DScene(zae::Camera* camera) : zae::Scene(camera)
{

}

void Game3DScene::Start()
{
	{
		auto e = entities.CreateEntity();
		e->SetName("TEST1");
		auto t = e->AddComponent<zae::Transform>();
		t->SetLocalPosition(zae::Vector3f());
		auto m = e->AddComponent<zae::MeshComponent>();
		m->SetMesh("TEST_MESH");
	}
}

void Game3DScene::Update(float delta)
{

}
