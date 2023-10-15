#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>
#include <zae/Engine/Graphics/Text/TextVertex.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>

namespace zae
{
	
	class Text
	{
	public:
		Text();
		Text(const std::shared_ptr<Font>& font);
		Text(const std::shared_ptr<Font>& font, const std::string& string);

		void SetString(const std::string& string);
		const std::string& GetString() const { return string; }

		void SetFont(const std::shared_ptr<Font>& font);
		const std::shared_ptr<Font>& GetFont() const { return font; }

		void SetSize(unsigned size);
		unsigned GetSize() const { return size; }

		void SetInternalColour(const Colour& internalColour);
		Colour GetInternalColour() const { return internal; }
		void SetExternalColour(const Colour& externalColour);
		Colour GetExternalColour() const { return external; }

		bool IsLoaded() const;
		bool IsDirty() const;

		void LoadText(float scaleX, float scaleY);
		void LoadText();

		const std::unique_ptr<Model>& GetModel() const { return model; }

		std::vector<TextVertex> verticies;
	private:
		bool isDirty;
		std::string string;
		std::shared_ptr<Font> font;
		std::unique_ptr<Model> model;
		unsigned size;
		Colour internal;
		Colour external;
	};

}