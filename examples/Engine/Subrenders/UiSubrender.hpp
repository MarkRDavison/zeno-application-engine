#pragma once

#include "TextModelVertex.hpp"

#include <zae/Engine/Graphics/Models/Model.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>


namespace test
{

	class UiSubrender : public zae::Subrender
	{
	public:
		explicit UiSubrender(const zae::Pipeline::Stage& stage);
		void Render(const zae::CommandBuffer& commandBuffer) override;

		void Init(std::unique_ptr<zae::Model>&& model);

	private:
		zae::PipelineGraphics pipeline;
		zae::UniformHandler uniformHandler;

		struct UniformBufferObject
		{
			zae::Matrix4 model;
			zae::Matrix4 view;
			zae::Matrix4 proj;
		} ubo;

		zae::DescriptorsHandler descriptorSet;

		zae::UniformHandler uniformScene;

		std::unique_ptr<zae::Image2d> image;
		std::unique_ptr<zae::Model> model;
	};

}