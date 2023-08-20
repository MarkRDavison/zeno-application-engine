#include <zae/Engine/Graphics/Text/TextSubrender.hpp>


namespace zae
{
	TextSubrender::TextSubrender(const Pipeline::Stage& pipelineStage) :
		Subrender(pipelineStage),
		pipeline(pipelineStage, { "shaders/text.vert", "shaders/text.frag" }, { VertexText::GetVertexInput() })
	{
	}

	void TextSubrender::Update()
	{
		for (auto& t : text)
		{
			t->Update();
		}
	}

	void TextSubrender::Render(const CommandBuffer& commandBuffer)
	{
		pipeline.BindPipeline(commandBuffer);

		for (auto& t : text)
		{
			t->CmdRender(commandBuffer, pipeline);
		}
	}

	void TextSubrender::AddText(std::shared_ptr<Text> instance)
	{
		text.push_back(instance);
	}
}