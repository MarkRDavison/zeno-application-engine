#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>
#include <string>

class CreepComponent : public zae::Component
{
public:
	std::string type;
};