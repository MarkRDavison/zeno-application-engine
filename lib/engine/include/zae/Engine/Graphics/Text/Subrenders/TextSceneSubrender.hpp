#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Text/Text.hpp>

namespace zae
{

	class TextSceneSubrender : public Subrender
	{
	public:
		explicit TextSceneSubrender(const Pipeline::Stage& stage);

		void Render(const CommandBuffer& commandBuffer) override;

	private:
		PipelineGraphics pipeline;
		UniformHandler uniformHandler;

		struct UniformBufferObject
		{
			Matrix4 model;
			Matrix4 view;
			Matrix4 proj;
		} ubo;

		DescriptorsHandler descriptorSet;

		UniformHandler uniformScene;
		PushHandler pushHandler;
	};

}