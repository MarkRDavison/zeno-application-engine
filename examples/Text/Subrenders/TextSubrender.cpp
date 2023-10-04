#include "TextSubrender.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>


TextSubrender::TextSubrender(const zae::Pipeline::Stage& stage) :
	zae::Subrender(stage),
	pipeline(
		stage,
		{ "shaders/testText.vert", "shaders/testText.frag" },
		{ TextModelVertex::GetVertexInput() },
		{  },
		zae::PipelineGraphics::Mode::Polygon,
		zae::PipelineGraphics::Depth::ReadWrite,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		VK_POLYGON_MODE_FILL,
		VK_CULL_MODE_BACK_BIT,
		VK_FRONT_FACE_COUNTER_CLOCKWISE
	),
	descriptorSet(pipeline)
{

}

void TextSubrender::Render(const zae::CommandBuffer& commandBuffer)
{
	pipeline.BindPipeline(commandBuffer);

	// These have to match the order in the shader
	uniformScene.Push("model", ubo.model);
	uniformScene.Push("view", ubo.view);
	uniformScene.Push("proj", ubo.proj);

	// This has to match the uniform setting in the shader
	descriptorSet.Push("UniformBufferObject", uniformScene);

	// Zap takes care of all complexities of Vulkan here and we can just push the image to the
	// sampler name in the shader
	descriptorSet.Push("texSampler", font->GetImage());

	// Set it to the pipeline
	descriptorSet.Update(pipeline);
	descriptorSet.BindDescriptor(commandBuffer, pipeline);

	// Draw the model, this time it knows it has a indexbuffer and does the indexed draw
	// It will also pass the UBO to the shader
	model->CmdRender(commandBuffer);
}

void TextSubrender::Init()
{
	ubo.proj[1][1] *= -1;
	ubo.model = zae::Matrix4();

	const std::vector<TextModelVertex> vertices = {
		{{-0.95f, -0.95f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{+0.95f, -0.95f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{+0.95f, +0.95f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.95f, +0.95f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
	};

	// Create a set of indices.
	const std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	// Create a model from that set of Vertices and indices.
	model = std::make_unique<zae::Model>(vertices, indices);

	font = std::make_shared<zae::Font>("fonts/Arial.ttf");
}