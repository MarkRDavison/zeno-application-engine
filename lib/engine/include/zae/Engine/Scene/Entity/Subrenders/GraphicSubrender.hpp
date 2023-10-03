#pragma once

#include <zae/Core/Math/Matrix4.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Subrender.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>

namespace zae
{

	class GraphicSubrender : public Subrender
	{
	public:
		explicit GraphicSubrender(const Pipeline::Stage& stage);

		void Render(const CommandBuffer& commandBuffer) override;

		void Init();

	private:
		PipelineGraphics pipeline;

		DescriptorsHandler descriptorSet;

		UniformHandler uniformScene;
		PushHandler pushHandler;

		struct UniformBufferObject
		{
			Matrix4 model;
			Matrix4 view;
			Matrix4 proj;
		} ubo;

		std::unique_ptr<Model> model;
	};

}