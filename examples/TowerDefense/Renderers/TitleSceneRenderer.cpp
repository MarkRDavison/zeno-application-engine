#include "TitleSceneRenderer.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Scene/Entity/Subrenders/GraphicSubrender.hpp>
#include <zae/Engine/Graphics/Mesh/Subrenders/MeshSubrender.hpp>
#include <zae/Engine/Graphics/Text/Subrenders/TextSceneSubrender.hpp>
#include <zae/Engine/Graphics/Mesh/Mesh.hpp>
#include <zae/Engine/Resources/Resources.hpp>

TitleSceneRenderer::TitleSceneRenderer()
{
	{
		std::vector<zae::Attachment> renderpassAttachments{
			{0, "depth", zae::Attachment::Type::Depth, false},
			{1, "swapchain", zae::Attachment::Type::Swapchain, false, VK_FORMAT_UNDEFINED, zae::Colour::Aqua},
		};

		std::vector<zae::SubpassType> renderpassSubpasses = {
			{ 0, { 0, 1 } }
		};

		AddRenderStage(std::make_unique<zae::RenderStage>(renderpassAttachments, renderpassSubpasses));
	}

}

void TitleSceneRenderer::Start()
{
	AddSubrender<zae::TextSceneSubrender>({ 0,0 });
}

void TitleSceneRenderer::Update()
{

}