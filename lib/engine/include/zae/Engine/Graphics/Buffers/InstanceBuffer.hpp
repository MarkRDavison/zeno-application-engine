#pragma once

#include <zae/Engine/Graphics/Buffers/Buffer.hpp>

namespace zae
{
	class InstanceBuffer : public Buffer
	{
	public:
		explicit InstanceBuffer(VkDeviceSize size);

		void Update(const CommandBuffer& commandBuffer, const void* newData);
	};
}
