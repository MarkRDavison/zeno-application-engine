#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>

class UiTextComponent : public zae::Component
{
public:
	bool hovered{ false };
	bool canInteract{ false };
};