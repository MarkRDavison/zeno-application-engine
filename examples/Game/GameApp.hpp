#pragma once

#include <zae/Engine/App.hpp>

class GameApp : public zae::App
{
public:
	GameApp();
	~GameApp();

	void Start() override;
	void Update() override;
};