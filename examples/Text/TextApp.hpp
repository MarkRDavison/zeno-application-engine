#pragma once

#include <zae/Engine/App.hpp>

class TextApp : public zae::App
{
public:
	TextApp();
	~TextApp();

	void Start() override;
	void Update() override;
};