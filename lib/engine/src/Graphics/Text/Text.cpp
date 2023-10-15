#include <zae/Engine/Graphics/Text/Text.hpp>
#include <zae/Engine/Devices/Windows.hpp>

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
		string(string),
		size(64),
		internal(Colour::White),
		external(Colour::Black)
	{
	}

	void Text::SetString(const std::string& string) 
	{
		isDirty |= string == this->string;
		this->string = string;
	}

	void Text::SetFont(const std::shared_ptr<Font>& font) 
	{
		isDirty |= font == this->font;
		this->font = font;
	}

	void Text::SetSize(unsigned size)
	{
		isDirty |= size == this->size;
		this->size = size;
	}

	void Text::SetInternalColour(const Colour& internalColour)
	{
		isDirty |= internalColour == this->internal;
		internal = internalColour;
	}

	void Text::SetExternalColour(const Colour& externalColour)
	{
		isDirty |= externalColour == this->external;
		external = externalColour;
	}

	bool Text::IsLoaded() const {
		return !string.empty() && model;
	}
	bool Text::IsDirty() const
	{
		return isDirty;
	}

	void AddVerticiesForGlyph(Vector2f cursor, float scaleX, float scaleY, const Font::Glyph& glyph, std::vector<TextVertex>& verticies)
	{
		const float xPos = cursor.x + glyph.bearingX * scaleX;
		const float yPos = cursor.y + (-glyph.sizeY + glyph.bearingY) * scaleY;

		const float w = glyph.sizeX * scaleX;
		const float h = glyph.sizeY * scaleY;

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

	void Text::LoadText(float scaleX, float scaleY)
	{
		if (string.empty()) { return; }
		const float TargetSize = static_cast<float>(size);
		const float finalScale = TargetSize / font->GetSize<float>();
		verticies.clear();

		Vector2f cursor;

		for (const auto& c : string)
		{
			if (c == ' ')
			{
				cursor.x += font->GetSpaceWidth<float>() * scaleX * finalScale;
				continue;
			}

			const auto& glyph = font->GetGlyph(c);
			if (glyph.has_value())
			{
				AddVerticiesForGlyph(cursor, finalScale * scaleX, finalScale * scaleY, glyph.value(), verticies);
				cursor.x += (glyph.value().advance >> 6) * finalScale * scaleX;
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
	void Text::LoadText()
	{
		LoadText(1.0f, 1.0f);
	}

}