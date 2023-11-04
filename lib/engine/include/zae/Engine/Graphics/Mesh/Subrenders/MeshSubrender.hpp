#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Subrender.hpp>
#include <zae/Engine/Graphics/Mesh/Mesh.hpp>

namespace zae
{

	class MeshSubrender : public Subrender
	{
	public:
		explicit MeshSubrender(const Pipeline::Stage& stage);

		void Render(const CommandBuffer& commandBuffer) override;

		void Init();

	private:
		PipelineGraphics pipeline;
		zae::UniformHandler uniformHandler;

		struct UniformBufferObject
		{
			Matrix4 view;
			Matrix4 proj;
		} ubo;

		DescriptorsHandler descriptorSet;

		UniformHandler uniformScene;
		PushHandler pushHandler;

	};

}