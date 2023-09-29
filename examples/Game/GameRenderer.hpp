#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>


class GameRenderer : public zae::Renderer
{
public:
	GameRenderer();

	void Start() override;
	void Update() override;
};
