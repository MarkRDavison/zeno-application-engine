#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>

#include <zae/Engine/Graphics/Subrender.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>

namespace zae
{

	class GuiSubrender : public Subrender
	{
	public:
		explicit GuiSubrender(const Pipeline::Stage& pipelineStage);

		void Render(const CommandBuffer& commandBuffer) override;

	private:
		PipelineGraphics pipeline;
	};

}