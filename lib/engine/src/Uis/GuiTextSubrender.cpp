#include <zae/Engine/Uis/GuiTextSubrender.hpp>
#include <zae/Engine/Uis/Uis.hpp>
#include <zae/Engine/Uis/Gui.hpp>
//#include <zae/Engine/Uis/Objects/UiText.hpp>
#include <zae/Engine/Graphics/Models/Vertex2d.hpp>
#include <zae/Engine/Graphics/Text/TextVertex.hpp>

namespace zae
{
	GuiTextSubrender::GuiTextSubrender(const Pipeline::Stage& pipelineStage) :
		Subrender(pipelineStage),
		pipeline(pipelineStage, 
			{ "shaders/guiText.vert", "shaders/guiText.frag" },
			{ zae::TextVertex::GetVertexInput() },
			{  },
			zae::PipelineGraphics::Mode::Polygon,
			zae::PipelineGraphics::Depth::ReadWrite,
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			VK_POLYGON_MODE_FILL,
			VK_CULL_MODE_BACK_BIT,
			VK_FRONT_FACE_COUNTER_CLOCKWISE
		)
	{
	}

	void GuiTextSubrender::Render(const CommandBuffer& commandBuffer)
	{
		const auto& objects = Uis::Get()->GetObjects();

		if (objects.empty()) { return; }

		pipeline.BindPipeline(commandBuffer);

		for (const auto& screenObject : objects)
		{
			//if (!screenObject->IsEnabled())
			//{
			//	continue;
			//}
			//
			//if (auto object = dynamic_cast<UiText*>(screenObject))
			//{
			//	object->CmdRender(commandBuffer, pipeline);
			//}
		}
	}

}