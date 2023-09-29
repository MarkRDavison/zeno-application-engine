#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Game/InputActionType.hpp>

#include <string>
#include <unordered_map>

namespace zae
{

	class InputActionManager : NonCopyable
	{
		InputActionManager() = default;
	public:
		static InputActionManager* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new InputActionManager();
			}

			return Instance;
		}

		void UpdateInputCache();
		void RegisterInputActionType(const InputActionType& action);
		bool IsActionInvoked(const std::string& name) const;

	private:
		static InputActionManager* Instance;
		std::unordered_map<std::string, InputActionType> actions;
		std::unordered_map<Key, bool> cachedKeys;
		std::unordered_map<MouseButton, bool> cachedButtons;
	};

}