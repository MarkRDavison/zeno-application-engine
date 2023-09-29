#include "TextRenderer.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>

namespace test
{

	TextRenderer::TextRenderer() :
		textSubrender(nullptr)
	{
		{
			std::vector<zae::Attachment> renderpassAttachments{
				{ 0, "swapchain", zae::Attachment::Type::Swapchain, false, VK_FORMAT_UNDEFINED, zae::Colour::Black },
			};

			std::vector<zae::SubpassType> renderpassSubpasses = {
				{ 0, { 0 } }
			};

			AddRenderStage(std::make_unique<zae::RenderStage>(renderpassAttachments, renderpassSubpasses));
		}
	}

	void TextRenderer::Start()
	{
		textSubrender = AddSubrender<zae::TextSubrender>({ 0, 0 });

		font = std::make_shared<zae::Font>("fonts/Arial.ttf");

		auto& t1 = text.emplace_back(std::make_unique<zae::Text>());
		t1->SetMaxSize({ 800.0f, 400.0f });
		t1->SetFont(font);
		t1->SetString("Abstract.jpqlLJAV\nhello world!\nhuh? Why?");
		t1->SetJustify(zae::Text::Justify::Centre);

		textSubrender->AddText(std::move(t1));
	}

	void TextRenderer::Update()
	{
		textSubrender->Update();
	}
}