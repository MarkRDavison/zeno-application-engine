#pragma once

#include <string>
#include <zae/Engine/Devices/WindowTypes.hpp>

namespace zae
{
	enum class ActionType
	{
		KEY,
		MOUSE_BUTTON,

		NONE
	};

	struct InputActionType
	{
		std::string name{};
		Key key{ Key::Unknown };
		MouseButton mouseButton{ MouseButton::COUNT };
		ActionType actionType{ ActionType::NONE };
	};
}