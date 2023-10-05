#include "TextSubrender.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>


TextSubrender::TextSubrender(const zae::Pipeline::Stage& stage) :
	zae::Subrender(stage),
	pipeline(
		stage,
		{ "shaders/testText.vert", "shaders/testText.frag" },
		{ zae::TextVertex::GetVertexInput() },
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
	const auto size = zae::Windows::Get()->GetWindow(0)->GetSize();
	ubo.view = zae::Matrix4::OrthographicMatrix(0.0f, size.x, 0.0f, size.y, -1.0f, 1000.0f);

	pipeline.BindPipeline(commandBuffer);

	// These have to match the order in the shader
	uniformScene.Push("model", ubo.model);
	uniformScene.Push("view", ubo.view);
	uniformScene.Push("proj", ubo.proj);
	uniformScene.Push("internalColor", zae::Colour::White);
	uniformScene.Push("outlineColor", zae::Colour::Black);

	// This has to match the uniform setting in the shader
	descriptorSet.Push("UniformBufferObject", uniformScene);

	// Zap takes care of all complexities of Vulkan here and we can just push the image to the
	// sampler name in the shader
	descriptorSet.Push("texSampler", font->GetImage());

	// Set it to the pipeline
	descriptorSet.Update(pipeline);
	descriptorSet.BindDescriptor(commandBuffer, pipeline);

	if (text->IsLoaded())
	{
		text->model->CmdRender(commandBuffer);
	}
	else
	{
		// Draw the model, this time it knows it has a indexbuffer and does the indexed draw
		// It will also pass the UBO to the shader
		model->CmdRender(commandBuffer);
	}
}

void TextSubrender::Init()
{
	const auto size = zae::Windows::Get()->GetWindow(0)->GetSize();
	ubo.view = zae::Matrix4::OrthographicMatrix(0.0f, size.x, 0.0f, size.y, -1.0f, 1000.0f);
	ubo.model = zae::Matrix4(1.0f).Translate({64.0f, 64.0f, 0.0f});
	ubo.proj[1][1] *= -1;

	const std::vector<zae::TextVertex> vertices = {
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
		{{+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
		{{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f}},
	};

	// Create a set of indices.
	const std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0
	};

	font = std::make_shared<zae::Font>("fonts/SegoeUi.ttf");

	text = std::make_shared<zae::Text>(font, "(c) Hello World! How are you going?!@#$%^&*{}<>");

	text->LoadText();

	// Create a model from that set of Vertices and indices.
	model = std::make_unique<zae::Model>(vertices, indices);
}