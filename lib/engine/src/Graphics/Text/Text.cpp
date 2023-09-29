#include <zae/Engine/Graphics/Text/Text.hpp>

#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Core/Utils/String.hpp>

namespace zae
{

	Text::Text() :
		justify(Justify::Left)
	{
		maxSize = { std::numeric_limits<float>::max() , std::numeric_limits<float>::max() };
	}

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
		uniformObject.Push("scale", 1.0f);
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

	void Text::SetMaxSize(const Vector2f& maxSize)
	{
		dirty |= this->maxSize == maxSize;
		this->maxSize = maxSize;
	}


	void Text::SetJustify(Justify justify)
	{
		dirty |= this->justify == justify;
		this->justify = justify;
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

		lastMaxSize = GetMaxSize();

		// Creates mesh data.
		auto lines = CreateStructure();

		auto numberLines = static_cast<uint32_t>(lines.size());

		auto vertices = CreateQuad(lines);

		model = std::make_unique<Model>(vertices);
		dirty = false;

#ifdef ZAE_DEBUG
		Log::Out("Text mesh with ", string.length(), " chars created in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif
	}

	std::vector<Text::Line> Text::CreateStructure() const
	{
		auto maxLength = lastMaxSize.x;

		std::vector<Line> lines;
		Line currentLine(font->GetSpaceWidth<float>(), maxLength);
		Word currentWord;

		auto formattedText = String::ReplaceAll(string, "\t", "	");
		auto textLines = String::Split(formattedText, '\n');


		for (uint32_t i = 0; i < textLines.size(); i++)
		{
			if (textLines.at(i).empty())
			{
				continue;
			}

			for (const auto& c : textLines.at(i))
			{
				auto ascii = static_cast<int32_t>(c);

				if (ascii == ' ')
				{
					if (!currentLine.AddWord(currentWord))
					{
						lines.emplace_back(currentLine);
						currentLine = { font->GetSpaceWidth<float>(),(float)maxLength };
						currentLine.AddWord(currentWord);
					}

					currentWord = {};
					continue;
				}

				if (auto character = font->GetGlyph(ascii))
				{
					currentWord.AddCharacter(*character, 0.0f/*kerning*/);
				}
			}

			if (i != textLines.size() - 1)
			{
				auto wordAdded = currentLine.AddWord(currentWord);
				lines.emplace_back(currentLine);
				currentLine = { font->GetSpaceWidth<float>(), (float)maxLength };

				if (!wordAdded)
				{
					currentLine.AddWord(currentWord);
				}

				currentWord = {};
			}
		}

		CompleteStructure(lines, currentLine, currentWord, maxLength);

		return lines;
	}
	void Text::CompleteStructure(std::vector<Line>& lines, Line& currentLine, const Word& currentWord, float maxLength) const
	{
		auto added = currentLine.AddWord(currentWord);

		if (!added)
		{
			lines.emplace_back(currentLine);
			currentLine = { font->GetSpaceWidth<float>(), maxLength };
			currentLine.AddWord(currentWord);
		}

		lines.emplace_back(currentLine);
	}
	std::vector<VertexText> Text::CreateQuad(const std::vector<Line>& lines) const
	{
		std::vector<VertexText> vertices;

		float cursorX = 0.0f;
		float cursorY = 0.0f;
		auto lineOrder = static_cast<int32_t>(lines.size());

		for (const auto& line : lines)
		{
			switch (justify)
			{
			case Justify::Left:
				cursorX = 0.0f;
				break;
			case Justify::Centre:
				cursorX = (line.maxLength - line.currentLineLength) / 2.0f;
				break;
			case Justify::Right:
				cursorX = line.maxLength - line.currentLineLength;
				break;
			case Justify::Fully:
				cursorX = 0.0f;
				break;
			}

			for (const auto& word : line.words)
			{
				for (const auto& letter : word.glyphs)
				{
					AddVerticesForGlyph(cursorX, cursorY, font->GetSize<float>(), letter, vertices);
					cursorX += 0.0f /* kerning */ + letter.advance;
				}

				if (justify == Justify::Fully && lineOrder > 1)
				{
					cursorX += (line.maxLength - line.currentWordsLength) / line.words.size();
				}
				else
				{
					cursorX += font->GetSpaceWidth<float>();
				}
			}

			cursorY += 0.0f /* leading */ + font->GetSize<float>() * 1.25f;// TODO: better value here
			lineOrder--;
		}

		return vertices;
	}

	void Text::AddVerticesForGlyph(float cursorX, float cursorY, float fontSize, const Font::Glyph& glyph, std::vector<VertexText>& vertices) const
	{
		const float fontGenerationSize = font->GetSize<float>();
		const float offset = fontGenerationSize / 16.0f;
		auto vertexX = cursorX + glyph.bearingX;
		auto vertexY = cursorY - glyph.bearingY + fontGenerationSize;
		auto vertexMaxX = vertexX + glyph.width;
		auto vertexMaxY = vertexY + glyph.height;

		const float texPixelHeight = fontGenerationSize;
		const float texPixelSize = fontGenerationSize;
		const float pixelHeight = glyph.height; // TODO: Width & height of characters that are wider than tall e.g. 'w'/'W'
		const float pixelWidth = glyph.width;   // TODO: Width & height of characters that are wider than tall e.g. 'w'/'W'

		const float aspectRatio = pixelWidth / pixelHeight;

		float heightRatio = 1.0f;
		float widthRatio = 1.0f;
		if (pixelHeight > pixelWidth)
		{
			heightRatio = texPixelHeight / pixelHeight;
		}
		else if (pixelHeight < pixelWidth)
		{
			widthRatio = texPixelHeight / pixelWidth;
		}

		const auto pixelInTextureWidth = pixelWidth * heightRatio + offset;
		const auto pixelInTextureHeight= pixelHeight * widthRatio + offset; // Offset?

		// TODO: Width & height of characters that are wider than tall e.g. 'w'/'W' probably actually need to fix here, take a horizontal slice
		auto textureX = 0.5f - ((pixelInTextureWidth) / 2.0f) / texPixelSize;
		auto textureY = 0.0f;
		auto textureMaxX = 0.5f + ((pixelInTextureWidth) / 2.0f) / texPixelSize;
		auto textureMaxY = 1.0f;

		AddVertex(vertexX, vertexMaxY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureMaxY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexMaxY, textureMaxX, textureY, glyph.layer, vertices);
		AddVertex(vertexX, vertexMaxY, textureX, textureY, glyph.layer, vertices);
		AddVertex(vertexX, vertexY, textureX, textureMaxY, glyph.layer, vertices);
		AddVertex(vertexMaxX, vertexY, textureMaxX, textureMaxY, glyph.layer, vertices);
	}

	void Text::AddVertex(float vx, float vy, float tx, float ty, float layer, std::vector<VertexText>& vertices) const
	{
		vertices.emplace_back(VertexText({ vx, vy }, { tx, ty, layer }));
	}
}