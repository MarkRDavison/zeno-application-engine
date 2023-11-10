#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>

class TowerWeaponComponent : public zae::Component
{
public:
	float minRange;
	float maxRange;
	std::string name;
	std::string projectileName;
	float elapsed;
	float firingInterval;
	zae::Entity* target{ nullptr };
};