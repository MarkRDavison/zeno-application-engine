#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>

namespace test
{

	class TestModelVertex
	{
	public:
		/*
		 * We need to describe how these are input to the shader
		 *
		 * from the shader:
		 *	layout(location = 0) in vec2 inPosition;
		 *	layout(location = 1) in vec3 inColor;
		 *	layout(location = 2) in vec2 inTexCoord;
		 *
		 */
		static zae::Shader::VertexInput GetVertexInput(uint32_t baseBinding = 0)
		{
			std::vector<VkVertexInputBindingDescription> bindingDescriptions = {
				{baseBinding, sizeof(TestModelVertex), VK_VERTEX_INPUT_RATE_VERTEX}
			};
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {
				{0, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(TestModelVertex, position)},
				{1, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(TestModelVertex, color)},
				{2, baseBinding, VK_FORMAT_R32G32_SFLOAT, offsetof(TestModelVertex, inTexCoord)}
			};
			return { bindingDescriptions, attributeDescriptions };
		}

		zae::Vector3f position;
		zae::Vector3f color;
		zae::Vector2f inTexCoord;
	};

}