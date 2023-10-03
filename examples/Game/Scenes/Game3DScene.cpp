#include "Game3DScene.hpp"
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/Graphic.hpp>

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
		auto g = e->AddComponent<zae::Graphic>();
		g->SetTexture("TEST_TEXTURE");
		g->SetSize({ 128.0f, 128.0f });
		g->SetOrigin(g->GetSize() / 2.0f); 
	}
	{
		auto e = entities.CreateEntity();
		e->SetName("TEST2");
		auto t = e->AddComponent<zae::Transform>();
		t->SetLocalPosition(zae::Vector3f(1.0f, 0.0f, 0.0f));
		auto g = e->AddComponent<zae::Graphic>();
		g->SetTexture("TEST_TEXTURE");
		g->SetSize({ 128.0f, 128.0f });
		g->SetOrigin(g->GetSize() / 2.0f);
	}
}

void Game3DScene::Update(float delta)
{

}
