#include <zae/Engine/Graphics/Text/Subrenders/TextSceneSubrender.hpp>

#include <zae/Engine/Scene/Entity/Components/TextComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/AnchorComponent.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Engine/Scene/Scenes.hpp>

namespace zae
{

	TextSceneSubrender::TextSceneSubrender(const zae::Pipeline::Stage& stage) :
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

	void TextSceneSubrender::Render(const zae::CommandBuffer& commandBuffer)
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

		const auto size = zae::Windows::Get()->GetWindow(0)->GetSize();
		ubo.view = zae::Matrix4::OrthographicMatrix(0.0f, size.x, size.y, 0.0f, -1.0f, 1000.0f);

		pipeline.BindPipeline(commandBuffer);

		// These have to match the order in the shader
		uniformScene.Push("view", ubo.view);
		uniformScene.Push("proj", ubo.proj);
		descriptorSet.Push("UniformBufferObject", uniformScene);

		for (auto& e : entities)
		{
			auto textComponent = e->GetComponent<TextComponent>();
			if (textComponent == nullptr) { continue; }
			auto transform = e->GetComponent<Transform>();
			if (transform == nullptr) { continue; }
			auto anchor = e->GetComponent<AnchorComponent>();

			auto text = textComponent->GetText();

			if (text->IsDirty())
			{
				text->LoadText();
			}

			pushHandler.Push("model", transform->GetWorldMatrix().Translate(Vector3f{
				0.0f,
				// TODO: the offset should be the size in pixels of the rendered text
				//		 not the font size?? But that means that each text will be different
				//size.y - text->GetModel()->GetHeight(),
				size.y - (float)text->GetSize(), 
				0.0f
			}));
			pushHandler.Push("internalColor", text->GetInternalColour());
			pushHandler.Push("outlineColor", text->GetExternalColour());

			descriptorSet.Push("texSampler", textComponent->GetFont()->GetImage());
			descriptorSet.Push("PushConstantObject", pushHandler);

			// Set it to the pipeline
			descriptorSet.Update(pipeline);
			descriptorSet.BindDescriptor(commandBuffer, pipeline);

			pushHandler.BindPush(commandBuffer, pipeline);

			text->GetModel()->CmdRender(commandBuffer);
		}
	}

}