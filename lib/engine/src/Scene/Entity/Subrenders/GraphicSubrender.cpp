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
			{ "shaders/testmodel.vert", "shaders/testmodel.frag" },
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

		for (auto& e : entities)
		{
			auto graphic = e->GetComponent<Graphic>();
			if (graphic == nullptr) { continue; }
			auto transform = e->GetComponent<Transform>();
			if (transform == nullptr) { continue; }

			ubo.model = transform->GetWorldMatrix();

			uniformScene.Push("model", ubo.model);
			descriptorSet.Push("UniformBufferObject", uniformScene);

			auto texture = Resources::Get()->Find<Image2d>(ResourceNode(graphic->GetTexture()));
			descriptorSet.Push("texSampler", texture);

			descriptorSet.Update(pipeline);
			descriptorSet.BindDescriptor(commandBuffer, pipeline);

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

		// Lets set up the camera viewpoint for now the models transform will be the Unit transform
		ubo.view = zae::Matrix4::LookAt(zae::Vector3f(2.0f, 2.0f, 2.0f), zae::Vector3f(0.0f, 0.0f, 0.0f), zae::Vector3f(0.0f, 0.0f, 1.0f));
		ubo.proj = zae::Matrix4::PerspectiveMatrix(zae::Math::Radians(45.0f), zae::Windows::Get()->GetWindow(0)->GetAspectRatio(), 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
		ubo.model = zae::Matrix4();
	}
}