#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>


class TitleSceneRenderer : public zae::Renderer
{
public:
	TitleSceneRenderer();

	void Start() override;
	void Update() override;
};
