#include "Game3DSceneSubrender.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>



Game3DSceneSubrender::Game3DSceneSubrender(const zae::Pipeline::Stage& stage) :
	zae::Subrender(stage),
	pipeline(
		stage,
		{ "shaders/testmodel.vert", "shaders/testmodel.frag" },
		{ TestModelVertex::GetVertexInput() },
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

void Game3DSceneSubrender::Render(const zae::CommandBuffer& commandBuffer)
{
	pipeline.BindPipeline(commandBuffer);

	// float time = (zae::Time::Now() - startTime).AsSeconds();
	// 
	// ubo.model = zae::Matrix4().Rotate(time * zae::Math::Radians(90.0f), zae::Vector3f(0.0f, 0.0f, 1.0f));

	// These have to match the order in the shader
	uniformScene.Push("model", ubo.model);
	uniformScene.Push("view", ubo.view);
	uniformScene.Push("proj", ubo.proj);

	// This has to match the uniform setting in the shader
	descriptorSet.Push("UniformBufferObject", uniformScene);

	// Zap takes care of all complexities of Vulkan here and we can just push the image to the
	// sampler name in the shader
	//descriptorSet.Push("texSampler", image);

	// Set it to the pipeline
	descriptorSet.Update(pipeline);
	descriptorSet.BindDescriptor(commandBuffer, pipeline);

	// Draw the model, this time it knows it has a indexbuffer and does the indexed draw
	// It will also pass the UBO to the shader
	//model->CmdRender(commandBuffer);
}