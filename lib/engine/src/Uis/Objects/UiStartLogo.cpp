#include <zae/Engine/Uis/Objects/UiStartLogo.hpp>
#include <zae/Engine/Timers.hpp>
#include <zae/Engine/Uis/Drivers/SlideDriver.hpp>
#include <zae/Engine/Uis/Constraints/PixelConstraint.hpp>
#include <zae/Engine/Uis/Constraints/RatioConstraint.hpp>

namespace zae
{
	UiStartLogo::UiStartLogo()
	{
		background.SetImage(Image2d::Create("gui/Black.png"));
		AddChild(&background);

		logo.GetConstraints()
			.SetWidth<PixelConstraint>(200)
			.SetHeight<RatioConstraint>(1.0f)
			.SetX<PixelConstraint>(0, UiAnchor::Centre)
			.SetY<PixelConstraint>(-150, UiAnchor::Centre);
		logo.SetImage(Image2d::Create("textures/logo.png"));
		AddChild(&logo);

		textCopyright.GetConstraints()
			.SetWidth<PixelConstraint>(460)
			.SetHeight<PixelConstraint>(64)
			.SetX<PixelConstraint>(0, UiAnchor::Centre)
			.SetY<PixelConstraint>(-128, UiAnchor::Centre);
		textCopyright.SetFont(Font::Create("Fonts/ProximaNova-Regular.ttf"));
		textCopyright.SetFontSize(16);
		//textCopyright.SetJustify(Text::Justify::Centre);
		textCopyright.SetTextColour(Colour::White, Colour::Black);
		textCopyright.SetString("Copyright (C) 2023, Zenotian Games - All Rights Reserved.");
		AddChild(&textCopyright);

		Timers::Get()->Once(this, 
			[this]()
			{
				SetAlphaDriver<SlideDriver>(1.0f, 0.0f, 1.4s);
			}, StartDelay);
	}

	void UiStartLogo::UpdateObject()
	{
		if (GetScreenAlpha() <= 0.0f && !finished)
		{
			finished = true;
			onFinished();
		}
	}

}