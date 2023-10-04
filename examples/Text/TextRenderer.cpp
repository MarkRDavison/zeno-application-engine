#include "TextRenderer.hpp"
#include "Subrenders/TextSubrender.hpp"
#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>

	TextRenderer::TextRenderer()
	{
		{
			// Define the attachments for the Pass
			// We are adding a depth buffer to the list of attachments
			std::vector<zae::Attachment> renderpassAttachments1{
				{0, "depth", zae::Attachment::Type::Depth, false},
				{1, "swapchain", zae::Attachment::Type::Swapchain, false, VK_FORMAT_UNDEFINED, zae::Colour::Aqua},
			};

			// Add the references to the attachments for the SubPass
			// In our case, SubPass 1 will be using Attachment 1
			// We have added the depth buffer to the list of attachments that the SubPass will
			// since our pipeline uses it now.
			std::vector<zae::SubpassType> renderpassSubpasses1 = {
				{ 0, { 0, 1 } }
			};
			AddRenderStage(std::make_unique<zae::RenderStage>(renderpassAttachments1, renderpassSubpasses1));
		}
	}

	void TextRenderer::Start()
	{
		auto subrender = AddSubrender<TextSubrender>({ 0,0 });
		subrender->Init();
	}

	void TextRenderer::Update()
	{
	}