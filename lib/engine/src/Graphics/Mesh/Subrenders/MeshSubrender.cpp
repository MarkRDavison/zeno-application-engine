#include <zae/Engine/Graphics/Mesh/Subrenders/MeshSubrender.hpp>
#include <zae/Engine/Scene/Entity/Components/MeshComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Scenes.hpp>

#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Graphics/Material/Material.hpp>

namespace zae
{

	MeshSubrender::MeshSubrender(const Pipeline::Stage& stage) :
		Subrender(stage),
		pipeline(
			stage,
			{ "shaders/material.vert", "shaders/material.frag" },
			{ Vertex3d::GetVertexInput() },
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

	void MeshSubrender::Render(const CommandBuffer& commandBuffer)
	{
		float delta = Engine::Get()->GetDeltaRender().AsSeconds<float>();
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

		auto camera = scene->GetCamera();

		ubo.view = camera->GetViewMatrix();
		ubo.proj = camera->GetProjectionMatrix();

		pipeline.BindPipeline(commandBuffer);

		uniformScene.Push("view", ubo.view);
		uniformScene.Push("proj", ubo.proj);
		descriptorSet.Push("UniformBufferObject", uniformScene);

		for (auto& e : entities)
		{
			auto meshComponent = e->GetComponent<MeshComponent>();
			if (meshComponent == nullptr) { continue; }
			auto transform = e->GetComponent<Transform>();
			if (transform == nullptr) { continue; }

			// TODO: PERF
			const auto& mesh = Resources::Get()->Find<Mesh>(ResourceNode(meshComponent->GetMesh()));

			pushHandler.Push("model", transform->GetWorldMatrix());

			for (const auto& model : mesh->GetModels())
			{
				// TODO: PERF
				auto material = Resources::Get()->Find<Material>(ResourceNode(model->GetMaterial()));

				if (!material)
				{
					continue; // TODO: Use default
				}

				// TODO: PERF
				auto diffuseMap = Resources::Get()->Find<Image2d>(ResourceNode(material->GetDiffuseMap()));

				if (!diffuseMap)
				{
					continue; // TODO: Use default
				}

				pushHandler.Push("diffuseColour", material->GetDiffuseColour());

				descriptorSet.Push("diffuseMap", diffuseMap);
				descriptorSet.Push("PushConstantObject", pushHandler);

				descriptorSet.Update(pipeline);
				descriptorSet.BindDescriptor(commandBuffer, pipeline);

				pushHandler.BindPush(commandBuffer, pipeline);

				model->CmdRender(commandBuffer);
			}
		}
	}

	void MeshSubrender::Init()
	{

	}
}