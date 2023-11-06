#pragma once

#include <zae/Engine/App.hpp>

class TowerDefenseApp : public zae::App
{
public:
	TowerDefenseApp();
	~TowerDefenseApp();

	void Start() override;
	void Update() override;

private:
	bool scene2d{ true };
};