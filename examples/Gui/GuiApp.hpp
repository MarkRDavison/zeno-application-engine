#pragma once

#include <zae/Engine/App.hpp>

class GuiApp : public zae::App
{
public:
	GuiApp();
	~GuiApp();

	void Start() override;
	void Update() override;
};