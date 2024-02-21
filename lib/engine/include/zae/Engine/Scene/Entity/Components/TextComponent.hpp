#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>
#include <zae/Engine/Graphics/Text/Text.hpp>

namespace zae
{

	class TextComponent : public Component
	{
	public:
		TextComponent() : text(std::make_shared<Text>()) {}

		void SetSize(unsigned size) { this->text->SetSize(size); }
		void SetFont(std::shared_ptr<Font> font) { this->text->SetFont(font); }
		void SetText(const std::string& text) { this->text->SetString(text); }
		std::shared_ptr<Font> GetFont() const { return this->text->GetFont(); }
		std::shared_ptr<Text> GetText() const { return this->text; }
		void SetInternalColour(Colour internalColour) { this->text->SetInternalColour(internalColour); }
		void SetExternalColour(Colour externalColour) { this->text->SetExternalColour(externalColour); }

	private:
		std::shared_ptr<Text> text;
	};

}