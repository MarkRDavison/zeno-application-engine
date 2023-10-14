#include "doctest.h"

#include <zae/Core/Math/Vector2.hpp>
#include <zae/Engine/Uis/Constraints/RelativeConstraint.hpp>
#include <zae/Engine/Uis/Constraints/PixelConstraint.hpp>
#include <zae/Engine/Uis/Constraints/RatioConstraint.hpp>
#include <zae/Engine/Uis/Constraints/UiConstraints.hpp>

TEST_CASE("Simple constraints")
{
	zae::Vector2i windowSize = { 1440, 900 };
	zae::UiConstraints canvas;

	canvas
		.SetX<zae::PixelConstraint>(0)
		.SetY<zae::PixelConstraint>(0)
		.SetWidth<zae::RelativeConstraint>(1.0f)
		.SetHeight<zae::RelativeConstraint>(1.0f);	
	
	canvas.GetWidth()->SetOffset(windowSize.x);
	canvas.GetHeight()->SetOffset(windowSize.y);

	CHECK(canvas.Update(nullptr));

	CHECK_EQ(0, canvas.GetX()->Get());
	CHECK_EQ(0, canvas.GetY()->Get());
	CHECK_EQ(windowSize.x, canvas.GetWidth()->Get());
	CHECK_EQ(windowSize.y, canvas.GetHeight()->Get());

	SUBCASE("With centered button with fixed size")
	{
		zae::UiConstraints button;
		button
			.SetX<zae::RelativeConstraint>(0.0f, zae::UiAnchor::Centre)
			.SetY<zae::RelativeConstraint>(0.0f, zae::UiAnchor::Centre)
			.SetWidth<zae::PixelConstraint>(100)
			.SetHeight<zae::PixelConstraint>(100);

		CHECK(button.Update(&canvas));

		CHECK_EQ(windowSize.x / 2, button.GetX()->Get());
		CHECK_EQ(windowSize.y / 2, button.GetY()->Get());
		CHECK_EQ(100, button.GetWidth()->Get());
		CHECK_EQ(100, button.GetHeight()->Get());
	}

	SUBCASE("With absolute button with fixed size")
	{
		zae::UiConstraints button;
		button
			.SetX<zae::PixelConstraint>(50)
			.SetY<zae::PixelConstraint>(50)
			.SetWidth<zae::PixelConstraint>(100)
			.SetHeight<zae::PixelConstraint>(100);

		button.Update(&canvas);

		CHECK_EQ(50, button.GetX()->Get());
		CHECK_EQ(50, button.GetY()->Get());
		CHECK_EQ(100, button.GetWidth()->Get());
		CHECK_EQ(100, button.GetHeight()->Get());
	}

	SUBCASE("With absolute button with ratio size")
	{
		zae::UiConstraints button;
		button
			.SetX<zae::PixelConstraint>(50)
			.SetY<zae::PixelConstraint>(50)
			.SetWidth<zae::PixelConstraint>(100)
			.SetHeight<zae::RatioConstraint>();

		button.Update(&canvas);

		CHECK_EQ(50, button.GetX()->Get());
		CHECK_EQ(50, button.GetY()->Get());
		CHECK_EQ(100, button.GetWidth()->Get());
		CHECK_EQ(100, button.GetHeight()->Get());
	}
}