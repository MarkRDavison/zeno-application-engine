#pragma once

#include "../TestModelVertex.hpp"

#include <zae/Engine/Graphics/Models/Model.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>


class Game3DSceneSubrender : public zae::Subrender
{
public:
	explicit Game3DSceneSubrender(const zae::Pipeline::Stage& stage);

	void Render(const zae::CommandBuffer& commandBuffer) override;

private:
	zae::PipelineGraphics pipeline;
	zae::UniformHandler uniformHandler;
	zae::DescriptorsHandler descriptorSet;
	zae::UniformHandler uniformScene;

	struct UniformBufferObject
	{
		zae::Matrix4 model;
		zae::Matrix4 view;
		zae::Matrix4 proj;
	} ubo;
};