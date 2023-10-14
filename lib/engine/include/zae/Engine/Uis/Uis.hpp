#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Uis/UiObject.hpp>
#include <vector>
#include <map>

namespace zae
{

	class Uis : NonCopyable
	{
		Uis();
	public:
		static Uis* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new Uis();
			}

			return Instance;
		}

		void Update(float delta);

		bool IsDown(MouseButton button);
		bool WasDown(MouseButton button);
		void CancelWasEvent(MouseButton button);

		UiObject& GetCanvas() { return canvas; }

		const std::vector<UiObject*>& GetObjects() const { return objects; };

	private:
		static Uis* Instance;

		class SelectorMouse
		{
		public:
			bool isDown;
			bool wasDown;
		};

		std::map<MouseButton, SelectorMouse> selectors;
		UiObject canvas;
		UiObject* cursorSelect = nullptr;
		std::vector<UiObject*> objects;
	};

}