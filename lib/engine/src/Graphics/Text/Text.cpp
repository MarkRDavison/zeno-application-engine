#include <zae/Engine/Graphics/Text/Text.hpp>

#include <zae/Engine/Devices/Windows.hpp>

namespace zae
{

	void Text::Update()
	{
		if (dirty)
		{
			LoadText();
		}

		const auto size = Windows::Get()->GetWindow(0)->GetSize();

		modelView = Matrix4::OrthographicMatrix(0.0f, size.x, 0.0f, size.y, 0.01f, 1000.0f);

		uniformObject.Push("modelView", GetModelView());
		uniformObject.Push("colour", Colour::White);
		uniformObject.Push("alpha", 1.0f);
	}

	bool Text::CmdRender(const CommandBuffer& commandBuffer, const PipelineGraphics& pipeline)
	{
		descriptorSet.Push("UniformObject", uniformObject);
		descriptorSet.Push("samplerMsdf", font->GetImage());

		if (!descriptorSet.Update(pipeline))
		{
			return false;
		}

		// Draws the object.
		descriptorSet.BindDescriptor(commandBuffer, pipeline);

		return model->CmdRender(commandBuffer);
	}

	void Text::SetString(const std::string& string)
	{
		dirty |= this->string != string;
		this->string = string;
	}

	void Text::SetFont(const std::shared_ptr<Font>& font)
	{
		dirty |= this->font == font;
		this->font = font;
	}

	void Text::LoadText()
	{
#ifdef ZAE_DEBUG
		auto debugStart = Time::Now();
#endif

		if (string.empty())
		{
			model = nullptr;
			return;
		}

		std::vector<VertexText> vertices;

		Vector2f cursor = { 0.0f, 0.0f };

		// https://freetype.org/freetype2/docs/glyphs/glyphs-3.html
		for (auto c : string)
		{
			auto glyph = font->GetGlyph(c);

			if (glyph.has_value())
			{
				AddVerticesForGlyph(cursor.x, cursor.y, 64.0f, glyph.value(), vertices);

				cursor.x += glyph.value().advance;
			}
			else
			{

				cursor.x += 64.0f;
			}
		}

		model = std::make_unique<Model>(vertices);
		dirty = false;

#ifdef ZAE_DEBUG
		Log::Out("Text mesh with ", string.length(), " chars created in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif
	}


	void Text::AddVerticesForGlyph(float cursorX, float cursorY, float fontSize, const Font::Glyph& glyph, std::vector<VertexText>& vertices)
	{
		const float offset = 2.0f;
		auto vertexX = cursorX + glyph.bearingX;
		auto vertexY = cursorY - glyph.bearingY + 64.0f;
		auto vertexMaxX = vertexX + glyph.width + offset;
		auto vertexMaxY = vertexY + glyph.height;

		const float texPixelHeight = 64.0f;
		const float texPixelSize = 64.0f;
		const float pixelHeight = glyph.height;
		const float pixelWidth = glyph.width + offset;

		const float aspectRatio = pixelWidth / pixelHeight;
		const float heightRatio = texPixelHeight / pixelHeight;
		const float heightRatioR = pixelHeight/ texPixelHeight;

		const auto pixelInTextureWidth = pixelWidth * heightRatio;

		const auto bearingOffsetX = 0.0f;

		// for 'l', width = 12, pixel width = 12
		auto textureX = 0.5f - ((pixelInTextureWidth) / 2.0f) / texPixelSize + bearingOffsetX;
		auto textureY = 0.0f;//glyph.textureCoordYtexPixelSize
		auto textureMaxX = 0.5f + ((pixelInTextureWidth) / 2.0f) / texPixelSize - bearingOffsetX;
		auto textureMaxY = 1.0f;//glyph.maxTextureCoordY;

		/*AddVertex(vertexX, vertexY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexMaxY, textureMaxX, textureMaxY, glyph.layer, vertices);
		AddVertex(vertexX, vertexMaxY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexMaxY, textureMaxX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureMaxY, glyph.layer, vertices);

		vertexY += 128.0f;
		vertexMaxY += 128.0f;*/

		AddVertex(vertexX, vertexMaxY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureMaxY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexMaxY, textureMaxX, textureY, glyph.layer, vertices);
		AddVertex(vertexX, vertexMaxY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexX, vertexY, textureX, textureMaxY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureMaxY, glyph.layer, vertices);



		//AddVertex(vertexMaxX, vertexMaxY, textureMaxX, textureMaxY, glyph.layer, vertices);
		//AddVertex(vertexX, vertexMaxY, textureX, textureMaxY, glyph.layer, vertices);
		//AddVertex(vertexX, vertexY, textureX, textureY, glyph.layer, vertices);
	}

	void Text::AddVertex(float vx, float vy, float tx, float ty, float layer, std::vector<VertexText>& vertices)
	{
		vertices.emplace_back(VertexText({ vx, vy }, { tx, ty, layer }));
	}
}