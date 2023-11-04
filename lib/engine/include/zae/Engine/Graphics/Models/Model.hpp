#pragma once

#include <cstring>
#include <functional>
#include <unordered_map>

#include <zae/Core/Math/Vector3.hpp>
#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Engine/Graphics/Buffers/Buffer.hpp>

namespace zae
{

	/**
	 * @brief Resource that represents a model vertex and index buffer.
	 */
	class Model : public Resource
	{
	public:
		/**
		 * Creates a new empty model.
		 */
		Model() = default;

		/**
		 * Creates a new model.
		 * @tparam T The vertex type.
		 * @param vertices The model vertices.
		 * @param indices The model indices.
		 */
		template<typename T>
		explicit Model(const std::vector<T>& vertices, const std::vector<uint32_t>& indices = {});

		bool CmdRender(const CommandBuffer& commandBuffer, uint32_t instances = 1) const;

		std::type_index GetTypeIndex() const override { return typeid(Model); }

		template<typename T>
		std::vector<T> GetVertices(std::size_t offset = 0) const;
		template<typename T>
		void SetVertices(const std::vector<T>& vertices);

		std::vector<uint32_t> GetIndices(std::size_t offset = 0) const;
		void SetIndices(const std::vector<uint32_t>& indices);

		std::vector<float> GetPointCloud() const;

		const Vector3f& GetMinExtents() const { return minExtents; }
		const Vector3f& GetMaxExtents() const { return maxExtents; }
		float GetWidth() const { return maxExtents.x - minExtents.x; }
		float GetHeight() const { return maxExtents.y - minExtents.y; }
		float GetDepth() const { return maxExtents.z - minExtents.z; }
		float GetRadius() const { return radius; }
		const Buffer* GetVertexBuffer() const { return vertexBuffer.get(); }
		const Buffer* GetIndexBuffer() const { return indexBuffer.get(); }
		uint32_t GetVertexCount() const { return vertexCount; }
		uint32_t GetIndexCount() const { return indexCount; }
		static VkIndexType GetIndexType() { return VK_INDEX_TYPE_UINT32; }

		void SetMaterial(const std::string& material) { this->material = material; }
		const std::string& GetMaterial() const { return this->material; }

	protected:
		template<typename T>
		void Initialize(const std::vector<T>& vertices, const std::vector<uint32_t>& indices = {});

	private:
		std::unique_ptr<Buffer> vertexBuffer;
		std::unique_ptr<Buffer> indexBuffer;
		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		Vector3f minExtents;
		Vector3f maxExtents;
		float radius = 0.0f;

		std::string material;
	};

	template<typename T>
	Model::Model(const std::vector<T>& vertices, const std::vector<uint32_t>& indices) :
		Model()
	{
		Initialize(vertices, indices);
	}

	template<typename T>
	std::vector<T> Model::GetVertices(std::size_t offset) const
	{
		Buffer vertexStaging(vertexBuffer->GetSize(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		CommandBuffer commandBuffer;

		VkBufferCopy copyRegion = {};
		copyRegion.size = vertexStaging.GetSize();
		vkCmdCopyBuffer(commandBuffer, vertexBuffer->GetBuffer(), vertexStaging.GetBuffer(), 1, &copyRegion);

		commandBuffer.SubmitIdle();

		void* verticesMemory;
		vertexStaging.MapMemory(&verticesMemory);
		std::vector<T> vertices(vertexCount);

		auto sizeOfSrcT = vertexStaging.GetSize() / vertexCount;

		for (uint32_t i = 0; i < vertexCount; i++)
		{
			std::memcpy(&vertices[i], static_cast<char*>(verticesMemory) + (i * sizeOfSrcT) + offset, sizeof(T));
		}

		vertexStaging.UnmapMemory();
		return vertices;
	}

	template<typename T>
	void Model::SetVertices(const std::vector<T>& vertices)
	{
		vertexBuffer = nullptr;
		vertexCount = static_cast<uint32_t>(vertices.size());

		if (vertices.empty())
			return;

		Buffer vertexStaging(sizeof(T) * vertices.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			vertices.data());
		vertexBuffer = std::make_unique<Buffer>(vertexStaging.GetSize(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		CommandBuffer commandBuffer;

		VkBufferCopy copyRegion = {};
		copyRegion.size = vertexStaging.GetSize();
		vkCmdCopyBuffer(commandBuffer, vertexStaging.GetBuffer(), vertexBuffer->GetBuffer(), 1, &copyRegion);

		commandBuffer.SubmitIdle();
	}

	template<typename T>
	void Model::Initialize(const std::vector<T>& vertices, const std::vector<uint32_t>& indices)
	{
		SetVertices(vertices);
		SetIndices(indices);

		minExtents = Vector3f::Infinity;
		maxExtents = -Vector3f::Infinity;

		for (const auto& vertex : vertices)
		{
			Vector3f position(vertex.position);
			minExtents = minExtents.Min(position);
			maxExtents = maxExtents.Max(position);
		}

		radius = std::max(minExtents.Length(), maxExtents.Length());
	}
}
