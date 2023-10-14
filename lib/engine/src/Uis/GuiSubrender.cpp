#include <zae/Engine/Uis/GuiSubrender.hpp>
#include <zae/Engine/Uis/Uis.hpp>
#include <zae/Engine/Uis/Gui.hpp>
#include <zae/Engine/Graphics/Models/Vertex2d.hpp>

namespace zae
{
	GuiSubrender::GuiSubrender(const Pipeline::Stage& pipelineStage) :
		Subrender(pipelineStage),
		pipeline(pipelineStage, 
			{ "shaders/gui.vert", "shaders/gui.frag" }, 
			{ Vertex2d::GetVertexInput() }
		)
	{
	}

	void GuiSubrender::Render(const CommandBuffer& commandBuffer)
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

			if (auto object = dynamic_cast<Gui*>(screenObject))
			{
				object->CmdRender(commandBuffer, pipeline);
			}
		}
	}

}