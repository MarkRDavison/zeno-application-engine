#include <zae/Game/InputActionManager.hpp>
#include <zae/Engine/Devices/Windows.hpp>

namespace zae
{
	InputActionManager* InputActionManager::Instance = nullptr;


	void InputActionManager::UpdateInputCache()
	{
		auto window = Windows::Get()->GetWindow(0);

		for (auto& [key, down] : cachedKeys)
		{
			down = window->GetKey(key) == InputAction::Press;
		}

		for (auto& [button, down] : cachedButtons)
		{
			down = window->GetMouseButton(button) == InputAction::Press;
		}
	}

	void InputActionManager::RegisterInputActionType(const InputActionType& action)
	{
		actions[action.name] = action;

		if (action.actionType == ActionType::KEY)
		{
			cachedKeys[action.key] = false;
		}
		
		if (action.actionType == ActionType::MOUSE_BUTTON)
		{
			cachedButtons[action.mouseButton] = false;
		}
	}

	bool InputActionManager::IsActionInvoked(const std::string& name) const
	{
		const auto actionIter = actions.find(name);
		if (actionIter != actions.end())
		{
			const auto& action = (*actionIter).second;

			auto window = Windows::Get()->GetWindow(0);

			switch (action.actionType)
			{
				case ActionType::KEY:
				{
					const auto& inputAction = window->GetKey(action.key);
					
					return inputAction == InputAction::Press && !cachedKeys.at(action.key);
				}
				break;
				case ActionType::MOUSE_BUTTON:
				{
					const auto& inputAction = window->GetMouseButton(action.mouseButton);

					return inputAction == InputAction::Press && !cachedButtons.at(action.mouseButton);
				}
				break;
			}
		}

		return false;
	}
}