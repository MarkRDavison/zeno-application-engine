#include "Game3DScene.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>

Game3DScene::Game3DScene(zae::Camera3D* camera) : zae::Scene3D(camera)
{

}

void Game3DScene::Start()
{
	auto e = entities.CreateEntity();
	e->SetName("TEST");
	e->AddComponent<zae::Transform>();
}

void Game3DScene::Update(float delta)
{

}
