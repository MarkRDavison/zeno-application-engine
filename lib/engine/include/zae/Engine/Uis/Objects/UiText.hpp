#pragma once

#include <zae/Engine/Uis/Gui.hpp>
#include <zae/Engine/Graphics/Text/Text.hpp>

namespace zae
{

	class UiText : public UiObject
	{
	public:
		explicit UiText();

		void UpdateObject() override;

		bool CmdRender(const CommandBuffer& commandBuffer, const PipelineGraphics& pipeline);

		void SetFont(const std::shared_ptr<Font>& font);
		const std::shared_ptr<Font>& GetFont() const { return text.GetFont(); }

		void SetString(const std::string& string);
		const std::string& GetString() const { return text.GetString(); }

		void SetFontSize(unsigned size);
		unsigned GetFontSize() const { return text.GetSize(); }

		void SetTextColour(
			const std::optional<Colour>& internal = std::nullopt,
			const std::optional<Colour>& external = std::nullopt);

	private:
		Text text;
		bool dirty = true;
		Vector2i lastSize;
		UniformHandler uniformScene;
		DescriptorsHandler descriptorSet;
	};

}