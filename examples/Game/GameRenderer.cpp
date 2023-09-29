#include "GameRenderer.hpp"

#include "Subrenders/ModelSubrender.hpp"

#include <zae/Engine/Graphics/Pipelines/Pipeline.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>

GameRenderer::GameRenderer()
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

void GameRenderer::Start()
{

	// Lets create a set of vertices and matching colors, a square this time.
	const std::vector<TestModelVertex> vertices = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

		{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
	};

	// Create a set of indices.
	const std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	// Create a model from that set of Vertices and indices.
	auto model = std::make_unique<zae::Model>(vertices, indices);

	auto modelScene = AddSubrender<ModelSubrender>({ 0, 0 });

	modelScene->Init(std::move(model));

	/*const std::vector<TestModelVertex> uiVertices = {
		{ { -1.0f, +0.0f, +0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
		{ { +0.0f, +0.0f, +0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { +0.0f, +1.0f, +0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
		{ { -1.0f, +1.0f, +0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
	};
	const std::vector<uint32_t> uiIndices = { 0, 1, 2, 0, 2, 3 };

	auto uiModel = std::make_unique<zae::Model>(uiVertices, uiIndices);

	auto uiScene = AddSubrender<UiSubrender>({ 0, 0 });

	uiScene->Init(std::move(uiModel));*/
}

void GameRenderer::Update()
{

}