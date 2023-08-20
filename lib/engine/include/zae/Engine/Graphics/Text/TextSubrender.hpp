#pragma once

#include <zae/Engine/Graphics/Subrender.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Text/Text.hpp>

namespace zae
{

	class TextSubrender : public Subrender
	{
	public:
		explicit TextSubrender(const Pipeline::Stage& pipelineStage);

		void Update();

		void Render(const CommandBuffer& commandBuffer) override;

		void AddText(std::shared_ptr<Text> instance);

	private:
		PipelineGraphics pipeline;

		std::vector<std::shared_ptr<Text>> text;
	};

}