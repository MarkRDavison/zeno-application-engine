#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>

namespace zae
{
	class TextVertex
	{
	public:
		/*
			* We need to describe how these are input to the shader
			*
			* from the shader:
			*	layout(location = 0) in vec2 inPosition;
			*	layout(location = 1) in vec2 inTexCoord;
			*
			*/
		static zae::Shader::VertexInput GetVertexInput(uint32_t baseBinding = 0)
		{
			std::vector<VkVertexInputBindingDescription> bindingDescriptions = {
				{baseBinding, sizeof(TextVertex), VK_VERTEX_INPUT_RATE_VERTEX}
			};
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {
				{0, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(TextVertex, position)},
				{1, baseBinding, VK_FORMAT_R32G32_SFLOAT, offsetof(TextVertex, inTexCoord)}
			};
			return { bindingDescriptions, attributeDescriptions };
		}

		zae::Vector3f position;
		zae::Vector2f inTexCoord;
	};

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

		bool IsLoaded() const;

		void LoadText();

	//private:
		bool isDirty;
		std::string string;
		std::shared_ptr<Font> font;
		std::unique_ptr<Model> model;
	};

}