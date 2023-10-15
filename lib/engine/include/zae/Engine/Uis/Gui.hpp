#pragma once

#include <zae/Engine/Uis/UiObject.hpp>
#include <zae/Engine/Uis/Drivers/UiDriver.hpp>
#include <zae/Engine/Graphics/Buffers/UniformHandler.hpp>
#include <zae/Engine/Graphics/Descriptors/DescriptorsHandler.hpp>
#include <zae/Engine/Graphics/Images/Image2d.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>

namespace zae
{

	class Gui : public UiObject
	{
	public:
		Gui();

		void UpdateObject() override;

		bool CmdRender(const CommandBuffer& commandBuffer, const PipelineGraphics& pipeline);

		const std::shared_ptr<Image2d>& GetImage() const { return image; }
		void SetImage(const std::shared_ptr<Image2d>& image) { this->image = image; }


		const Vector4f& GetNinePatches() const { return ninePatches; }
		void SetNinePatches(const Vector4f& ninePatches) { this->ninePatches = ninePatches; }

		UiDriver<Colour>* GetColourDriver() const { return colourDriver.get(); }
		template<template<typename> typename T, typename... Args>
		auto SetColourDriver(Args &&... args) -> std::enable_if_t<std::is_convertible_v<T<Colour>*, UiDriver<Colour>*>, void>
		{
			colourDriver = std::make_unique<T<Colour>>(std::forward<Args>(args)...);
		}

	private:
		virtual const std::unique_ptr<Model>& GetModel() const { return model; }

	private:
		DescriptorsHandler descriptorSet;
		UniformHandler uniformObject;

		std::unique_ptr<Model> model; // TODO: Static???
		std::shared_ptr<Image2d> image;
		uint32_t numberOfRows = 1;
		uint32_t selectedRow = 0;
		Vector2f atlasOffset;
		Vector2f atlasScale = Vector2f::One;
		Vector4f ninePatches; // TODO: Use UiTransform

		std::unique_ptr<UiDriver<Colour>> colourDriver;

	};
}