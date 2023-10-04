#pragma once

#include "../TextModelVertex.hpp"

#include <zae/Engine/Graphics/Models/Model.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Text/Font.hpp>

class TextSubrender : public zae::Subrender
{
public:
	explicit TextSubrender(const zae::Pipeline::Stage& stage);

	void Render(const zae::CommandBuffer& commandBuffer) override;

	void Init();

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

	std::shared_ptr<zae::Font> font;
	std::unique_ptr<zae::Model> model;
};