#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>


class TextRenderer : public zae::Renderer
{
public:
	TextRenderer();

	void Start() override;
	void Update() override;

};