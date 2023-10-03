#pragma once

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Core/Math/Vector3.hpp>
#include <zae/Core/Math/Rect.hpp>
#include <zae/Engine/Scene/Entity/Component.hpp>
#include <zae/Engine/Graphics/Renderer.hpp>
#include <string>

namespace zae
{

	class GraphicModelVertex
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
				{baseBinding, sizeof(GraphicModelVertex), VK_VERTEX_INPUT_RATE_VERTEX}
			};
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {
				{0, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GraphicModelVertex, position)},
				{1, baseBinding, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GraphicModelVertex, color)},
				{2, baseBinding, VK_FORMAT_R32G32_SFLOAT, offsetof(GraphicModelVertex, inTexCoord)}
			};
			return { bindingDescriptions, attributeDescriptions };
		}

		zae::Vector3f position;
		zae::Vector3f color;
		zae::Vector2f inTexCoord;
	};

	class Graphic : public Component
	{
	public:
		void SetTexture(const std::string& texture) { this->texture = texture; }
		std::string GetTexture() const { return texture; }

		void SetSize(const Vector2f& size) { this->size = size; }
		Vector2f GetSize() const { return size; }

		void SetTextureBounds(const Rect& bounds) { this->bounds = bounds; }
		Rect GetTextureBounds() const { return bounds; }

		void SetOrigin(const Vector2f& origin) { this->origin = origin; }
		Vector2f GetOrigin() const { return origin; }

	private:
		std::string texture;
		Vector2f size;
		Vector2f origin;
		Rect bounds;
	};

}