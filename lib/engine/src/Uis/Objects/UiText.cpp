#include <zae/Engine/Uis/Objects/UiText.hpp>

namespace zae
{

	UiText::UiText()
	{

	}


	void UiText::UpdateObject()
	{
		dirty |= GetScreenSize() != lastSize;
		if (dirty)
		{
			text.LoadText(1.0f / 64.0f);
		}

		auto proj = Matrix4(1.0f);
		proj[1][1] *= -1;

		// Updates uniforms.
		uniformScene.Push("modelView", proj * GetModelView());
		uniformScene.Push("alpha", GetScreenAlpha());
		uniformScene.Push("scale", 1.0f);
		uniformScene.Push("internalColor", zae::Colour::White);
		uniformScene.Push("outlineColor", zae::Colour::Black);
	}

	bool UiText::CmdRender(const CommandBuffer& commandBuffer, const PipelineGraphics& pipeline)
	{

		// This has to match the uniform setting in the shader
		descriptorSet.Push("UniformBufferObject", uniformScene);

		// Zap takes care of all complexities of Vulkan here and we can just push the image to the
		// sampler name in the shader
		descriptorSet.Push("texSampler", GetFont()->GetImage());

		// Set it to the pipeline
		if (!descriptorSet.Update(pipeline))
		{
			return false;
		}

		descriptorSet.BindDescriptor(commandBuffer, pipeline);

		text.GetModel()->CmdRender(commandBuffer);

		return true;
	}

	void UiText::SetFont(const std::shared_ptr<Font>& font)
	{
		if (GetFont() != font)
		{
			dirty = true;
			text.SetFont(font);
		}
	}

	void UiText::SetString(const std::string& string)
	{
		if (GetString() != string)
		{
			dirty = true;
			text.SetString(string);
		}
	}
}