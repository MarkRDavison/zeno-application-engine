#pragma once

#include <zae/Engine/Graphics/Images/Image.hpp>

namespace zae
{
	/**
	 * @brief Resource that represents a depth stencil image.
	 */
	class ImageDepth : public Image
	{
	public:
		explicit ImageDepth(const Vector2ui& extent, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT);
	};
}
