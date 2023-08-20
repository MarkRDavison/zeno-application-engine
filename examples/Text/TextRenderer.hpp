#pragma once

#include <zae/Engine/Graphics/Renderer.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>
#include <zae/Engine/Graphics/Text/Text.hpp>
#include <zae/Engine/Graphics/Text/TextSubrender.hpp>

namespace test
{

	class TextRenderer : public zae::Renderer
	{
	public:
		TextRenderer();

		void Start() override;
		void Update() override;

	private:
		std::vector<std::unique_ptr<zae::Text>> text;
		std::shared_ptr<zae::Font> font;
		zae::TextSubrender* textSubrender;
	};

}