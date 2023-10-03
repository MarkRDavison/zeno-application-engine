#include <zae/Engine/Scene/Entity/Subrenders/GraphicSubrender.hpp>
#include <zae/Engine/Scene/Entity/Components/Graphic.hpp>
#include <zae/Engine/Scene/Scenes.hpp>

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>

namespace zae
{
	GraphicSubrender::GraphicSubrender(const Pipeline::Stage& stage) :
		Subrender(stage),
		pipeline(
			stage,
			{ "shaders/defaultScene.vert", "shaders/defaultScene.frag" },
			{ GraphicModelVertex::GetVertexInput() },
			{  },
			PipelineGraphics::Mode::Polygon,
			PipelineGraphics::Depth::ReadWrite,
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			VK_POLYGON_MODE_FILL,
			VK_CULL_MODE_BACK_BIT,
			VK_FRONT_FACE_COUNTER_CLOCKWISE
		),
		descriptorSet(pipeline)
	{

	}

	void GraphicSubrender::Render(const CommandBuffer& commandBuffer)
	{
		auto scene = Scenes::Get()->GetScene();

		if (scene == nullptr || !scene->IsActive())
		{
			return;
		}

		const auto& entities = scene->QueryAll();

		if (entities.empty())
		{
			return;
		}

		pipeline.BindPipeline(commandBuffer);

		uniformScene.Push("view", ubo.view);
		uniformScene.Push("proj", ubo.proj);
		descriptorSet.Push("UniformBufferObject", uniformScene);

		for (auto& e : entities)
		{
			auto graphic = e->GetComponent<Graphic>();
			if (graphic == nullptr) { continue; }
			auto transform = e->GetComponent<Transform>();
			if (transform == nullptr) { continue; }

			ubo.model = transform->GetWorldMatrix();

			pushHandler.Push("model", ubo.model);

			descriptorSet.Push("PushConstantObject", pushHandler);

			auto texture = Resources::Get()->Find<Image2d>(ResourceNode(graphic->GetTexture()));
			descriptorSet.Push("texSampler", texture);

			descriptorSet.Update(pipeline);
			descriptorSet.BindDescriptor(commandBuffer, pipeline);
			pushHandler.BindPush(commandBuffer, pipeline);
			model->CmdRender(commandBuffer);
		}
	}

	void GraphicSubrender::Init()
	{
		const std::vector<GraphicModelVertex> vertices = 
		{
			{ { -1.0f, +0.0f, +0.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
			{ { +0.0f, +0.0f, +0.0f }, { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
			{ { +0.0f, +1.0f, +0.0f }, { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { -1.0f, +1.0f, +0.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
		};
		const std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

		model = std::make_unique<Model>(vertices, indices);

		auto scene = Scenes::Get()->GetScene();
		if (scene != nullptr)
		{
			const auto& camera = scene->GetCamera();
			ubo.view = camera->GetViewMatrix();
			ubo.proj = camera->GetProjectionMatrix();
		}
		
		ubo.proj[1][1] *= -1;
		ubo.model = zae::Matrix4();
	}
}