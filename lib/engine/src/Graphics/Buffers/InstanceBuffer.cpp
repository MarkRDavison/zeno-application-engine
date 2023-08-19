#include <zae/Engine/Graphics/Buffers/InstanceBuffer.hpp>

#include <cstring>

#include <zae/Engine/Graphics/Graphics.hpp>

namespace zae
{
	InstanceBuffer::InstanceBuffer(VkDeviceSize size) :
		Buffer(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
	{
	}

	void InstanceBuffer::Update(const CommandBuffer& commandBuffer, const void* newData)
	{
		void* data;
		MapMemory(&data);
		std::memcpy(data, newData, static_cast<std::size_t>(size));
		UnmapMemory();
	}
}
