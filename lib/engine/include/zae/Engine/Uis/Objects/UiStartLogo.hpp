#pragma once

#include <zae/Core/Utils/Signal.hpp>
#include <zae/Engine/Uis/Gui.hpp>
#include <zae/Engine/Uis/Objects/UiText.hpp>

namespace zae
{
	class UiStartLogo : public UiObject
	{
	public:
		explicit UiStartLogo();

		void UpdateObject() override;

		bool IsFinished() const { return finished; }
		Signal<>& OnFinished() { return onFinished; }

#ifdef ZAE_DEBUG
		constexpr static Time StartDelay = 5s;//1s;
#else
		constexpr static Time StartDelay = 3s;
#endif

	private:
		Gui background;
		Gui logo;
		UiText textCopyright;

		bool finished = false;

		Signal<> onFinished;
	};
}
