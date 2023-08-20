#include "UiSubrender.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>

namespace test
{
	UiSubrender::UiSubrender(const zae::Pipeline::Stage& stage) :
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

	void UiSubrender::Render(const zae::CommandBuffer& commandBuffer)
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
		descriptorSet.Push("texSampler", image);

		// Set it to the pipeline
		descriptorSet.Update(pipeline);
		descriptorSet.BindDescriptor(commandBuffer, pipeline);

		// Draw the model, this time it knows it has a indexbuffer and does the indexed draw
		// It will also pass the UBO to the shader
		model->CmdRender(commandBuffer);
	}

	void UiSubrender::Init(std::unique_ptr<zae::Model>&& model)
	{
		this->model = std::move(model);

		const auto size = zae::Windows::Get()->GetWindow(0)->GetSize();

		// Lets set up the camera viewpoint for now the models transform will be the Unit transform
		ubo.view = zae::Matrix4();
		ubo.proj = zae::Matrix4::OrthographicMatrix(-1.0f, +1.0f, -1.0f, +1.0f, 0.01f, 1000.0f);
		ubo.proj[1][1] *= -1;
		ubo.model = zae::Matrix4();

		// Lets create an image to be the texture of the object, we will load from the resources system.
		image = std::make_unique<zae::Image2d>("textures/logo.png");
	}
}