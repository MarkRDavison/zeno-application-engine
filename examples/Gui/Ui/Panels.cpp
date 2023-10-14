#include "Panels.hpp"
#include <zae/Engine/Graphics/Images/Image2d.hpp>


Panels::Panels()
{
	//background.SetImage(zae::Image2d::Create("gui/White.png"));
	//AddChild(&background);
	//
	////button0.SetTransform({UiButtonInput::Size, UiAnchor::LeftTop, {0, GetNextY()}});
	//button0.GetConstraints()
	//	.SetX<zae::RelativeConstraint>(0.1f, zae::UiAnchor::Left)
	//	.SetY<zae::RelativeConstraint>(0.1f, zae::UiAnchor::Top)
	//	.SetWidth<zae::RelativeConstraint>(0.8f)
	//	.SetHeight<zae::RelativeConstraint>(0.8f);
	//
	//button0.SetTitle("Button");
	//button0.OnClick().registerCallback(
	//	[](zae::MouseButton button) -> void {
	//		zae::Log::Info("Panel button clicked", '\n');
	//	});
	//gui0.AddChild(&button0);
	//
	////gui0.SetManipulate(zae::UiManipulate::All);
	////gui0.SetScrollBars(zae::ScrollBar::Both);
	//gui0.SetBackgroundColor(zae::UiButtonInput::BackgroundColour);
	//AddChild(&gui0);
}

void Panels::UpdateObject()
{

}