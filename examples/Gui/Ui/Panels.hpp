#pragma once

#include <zae/Engine/Uis/Gui.hpp>
#include <zae/Engine/Uis/UiObject.hpp>

class Panels : public zae::UiObject
{
public:
	Panels();

	void UpdateObject() override;

private:
	zae::Gui background;
};