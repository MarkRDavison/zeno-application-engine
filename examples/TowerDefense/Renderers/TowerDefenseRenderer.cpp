#include "TowerDefenseRenderer.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Scene/Entity/Subrenders/GraphicSubrender.hpp>
#include <zae/Engine/Graphics/Mesh/Subrenders/MeshSubrender.hpp>
#include <zae/Engine/Graphics/Mesh/Mesh.hpp>
#include <zae/Engine/Resources/Resources.hpp>

TowerDefenseRenderer::TowerDefenseRenderer()
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

void TowerDefenseRenderer::Start()
{
	auto subrender = AddSubrender<zae::GraphicSubrender>({ 0,0 });
	subrender->Init();
	AddSubrender<zae::MeshSubrender>({ 0,0 });
}

void TowerDefenseRenderer::Update()
{

}