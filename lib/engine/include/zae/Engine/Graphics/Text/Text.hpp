#pragma once

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Core/Math/Vector3.hpp>
#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>

namespace zae
{

	class VertexText
	{
	public:
		VertexText() = default;
		VertexText(const Vector2f& position, const Vector3f& uv) :
			position(position),
			uv(uv)
		{
		}

		static Shader::VertexInput GetVertexInput(uint32_t baseBinding = 0)
		{
			std::vector<VkVertexInputBindingDescription> bindingDescriptions = {
				{baseBinding, sizeof(VertexText), VK_VERTEX_INPUT_RATE_VERTEX}
			};
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {
				{0, baseBinding, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexText, position)},
				{1, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexText, uv)}
			};
			return { bindingDescriptions, attributeDescriptions };
		}

		bool operator==(const VertexText& rhs) const
		{
			return position == rhs.position && uv == rhs.uv;
		}

		bool operator!=(const VertexText& rhs) const
		{
			return !operator==(rhs);
		}

		Vector2f position;
		Vector3f uv;
	};

	class Text
	{
		friend class Font;
	public:
		enum class Justify
		{
			Left, Centre, Right, Fully
		};

		Text();

		bool CmdRender(const CommandBuffer& commandBuffer, const PipelineGraphics& pipeline);

		void Update();

		void SetString(const std::string& string);
		const Model* GetModel() const { return model.get(); }

		void SetFont(const std::shared_ptr<Font>& font);
		const std::shared_ptr<Font>& GetFont() const { return font; }

		void SetMaxSize(const Vector2f& maxSize);
		const Vector2f& GetMaxSize() const { return maxSize; }

		void SetJustify(Justify justify);
		Justify GetJustify() const { return justify; }

		const Matrix4& GetModelView() const { return modelView; }

	private:
		class Word
		{
		public:
			Word() = default;

			void AddCharacter(const Font::Glyph& glyph, float kerning)
			{
				glyphs.emplace_back(glyph);
				width += kerning + glyph.advance;
			}

			std::vector<Font::Glyph> glyphs;
			float width = 0.0f;
		};

		class Line
		{
		public:
			Line(float spaceWidth, float maxLength) :
				maxLength(maxLength),
				spaceSize(spaceWidth)
			{
			}

			bool AddWord(const Word& word)
			{
				auto additionalLength = word.width;
				additionalLength += !words.empty() ? spaceSize : 0.0f;

				if (currentLineLength + additionalLength <= maxLength)
				{
					words.emplace_back(word);
					currentWordsLength += word.width;
					currentLineLength += additionalLength;
					return true;
				}

				return false;
			}

			float maxLength;
			float spaceSize;

			std::vector<Word> words;
			float currentWordsLength = 0.0f;
			float currentLineLength = 0.0f;
		};

	private:
		void LoadText();
		std::vector<Line> CreateStructure() const;
		void CompleteStructure(std::vector<Line>& lines, Line& currentLine, const Word& currentWord, float maxLength) const;
		std::vector<VertexText> CreateQuad(const std::vector<Line>& lines) const;
		void AddVerticesForGlyph(float cursorX, float cursorY, float fontSize, const Font::Glyph& glyph, std::vector<VertexText>& vertices) const;
		void AddVertex(float vx, float vy, float tx, float ty, float layer, std::vector<VertexText>& vertices) const;

	private:
		bool dirty = true;
		std::string string;

		Justify justify;

		Matrix4 modelView;

		DescriptorsHandler descriptorSet;
		UniformHandler uniformObject;

		std::unique_ptr<Model> model;
		std::shared_ptr<Font> font;

		Vector2f maxSize;
		Vector2f lastMaxSize;
	};

}