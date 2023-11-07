#include "SceneTransitions.hpp"
#include "OptionsScene.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"
#include "../Renderers/TowerDefenseRenderer.hpp"
#include "../Renderers/TitleSceneRenderer.hpp"
#include <zae/Engine/Scene/Scenes.hpp>


void SceneTransitions::SetGameScene()
{
	zae::Graphics::Get()->SetRenderer(std::make_unique<TowerDefenseRenderer>());
	zae::Scenes::Get()->SetScene(std::make_unique<GameScene>());
}
void SceneTransitions::SetTitleScene()
{
	zae::Graphics::Get()->SetRenderer(std::make_unique<TitleSceneRenderer>());
	zae::Scenes::Get()->SetScene(std::make_unique<TitleScene>());
}
void SceneTransitions::SetOptionsScene()
{
	zae::Graphics::Get()->SetRenderer(std::make_unique<TitleSceneRenderer>());
	zae::Scenes::Get()->SetScene(std::make_unique<OptionsScene>());
}