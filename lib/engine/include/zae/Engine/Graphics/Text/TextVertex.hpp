#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>

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

}