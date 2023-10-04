#include <zae/Engine/Graphics/Text/Text.hpp>

namespace zae
{

	Text::Text(
	) : Text(nullptr) {}

	Text::Text(
		const std::shared_ptr<Font>& font
	) : Text(font, "") {}

	Text::Text(
		const std::shared_ptr<Font>& font, 
		const std::string& string
	) : 
		isDirty(true),
		font(font),
		string(string)
	{
	}

	void Text::SetString(const std::string& string) 
	{
		isDirty |= string == this->string;
	}

	void Text::SetFont(const std::shared_ptr<Font>& font) 
	{
		isDirty |= font == this->font;
	}

	bool Text::IsLoaded() const {
		return !string.empty() && model;
	}

	void AddVerticiesForGlyph(Vector2f cursor, float scale, const Font::Glyph& glyph, std::vector<TextVertex>& verticies)
	{
		const float xPos = cursor.x + glyph.bearingX * scale;
		const float yPos = cursor.y + (-glyph.sizeY + glyph.bearingY) * scale;

		const float w = glyph.sizeX * scale;
		const float h = glyph.sizeY * scale;

		const float tx = glyph.textureX;
		const float ty = glyph.textureY;
		const float tw = glyph.sizeX;
		const float th = glyph.sizeY;

		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos, yPos + h, 0.0f), .inTexCoord = Vector2f(tx, ty) });
		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos, yPos, 0.0f), .inTexCoord = Vector2f(tx, ty + th) });
		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos + w, yPos, 0.0f), .inTexCoord = Vector2f(tx + tw, ty + th) });

		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos, yPos + h, 0.0f), .inTexCoord = Vector2f(tx, ty) });
		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos + w, yPos, 0.0f), .inTexCoord = Vector2f(tx + tw, ty + th) });
		verticies.emplace_back(TextVertex{ .position = Vector3f(xPos + w, yPos + h, 0.0f), .inTexCoord = Vector2f(tx + tw, ty) });
	}

	void Text::LoadText()
	{
		const float scale = 1.0f;
		std::vector<TextVertex> verticies;

		Vector2f cursor;

		for (const auto& c : string)
		{
			if (c == ' ')
			{
				cursor.x += font->GetSpaceWidth<float>();
				continue;
			}

			const auto& glyph = font->GetGlyph(c);
			if (glyph.has_value())
			{
				AddVerticiesForGlyph(cursor, scale, glyph.value(), verticies);
				cursor.x += (glyph.value().advance >> 6) * scale;
			}

		}

		const auto fontTextureSize = font->GetImage()->GetSize();

		for (auto& vertex : verticies)
		{
			vertex.inTexCoord.x /= fontTextureSize.x;
			vertex.inTexCoord.y /= fontTextureSize.y;
		}

		model = std::make_unique<Model>(verticies);
	}

}