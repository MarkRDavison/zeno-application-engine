#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>


class TowerDefenseRenderer : public zae::Renderer
{
public:
	TowerDefenseRenderer();

	void Start() override;
	void Update() override;
};
