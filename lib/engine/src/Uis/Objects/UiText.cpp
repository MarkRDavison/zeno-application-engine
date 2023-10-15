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
			const auto& size = Vector2f(GetScreenSize());
			// TODO: scale text height to font size based on screen resolution
			text.LoadText(1.0f / text.GetFont()->GetSize<float>(), 1.0f / text.GetFont()->GetSize<float>() * (size.x / size.y));
		}

		auto proj = Matrix4(1.0f);
		proj[1][1] *= -1;

		// Updates uniforms.
		uniformScene.Push("modelView", proj * GetModelView());
		uniformScene.Push("alpha", GetScreenAlpha());
		uniformScene.Push("scale", 0.125f);
		uniformScene.Push("internalColor", text.GetInternalColour());
		uniformScene.Push("outlineColor", text.GetExternalColour());
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

	void UiText::SetFontSize(unsigned size)
	{
		if (GetFontSize() != size)
		{
			dirty = true;
			text.SetSize(size);
		}
	}

	void UiText::SetTextColour(
		const std::optional<Colour>& internal,
		const std::optional<Colour>& external)
	{
		if (internal.has_value())
		{
			text.SetInternalColour(internal.value());
		}
		if (external.has_value())
		{
			text.SetExternalColour(external.value());
		}
	}
}