#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>


class GuiRenderer : public zae::Renderer
{
public:
	GuiRenderer();

	void Start() override;
	void Update() override;
};
