#include <zae/Engine/Uis/Uis.hpp>
#include <zae/Engine/Uis/Constraints/PixelConstraint.hpp>

namespace zae
{

	Uis* Uis::Instance = nullptr;

	Uis::Uis()
	{
		canvas
			.GetConstraints()
			.SetWidth<PixelConstraint>(0)
			.SetHeight<PixelConstraint>(0);

		for (uint8_t m = 0; m < (uint8_t)MouseButton::COUNT; ++m)
		{
			auto button = (MouseButton)m;
			selectors.emplace(button, SelectorMouse());
		}
	}


	void Uis::Update(float delta)
	{
		for (auto& [button, selector] : selectors)
		{
			auto isDown = Windows::Get()->GetWindow(0)->GetMouseButton(button) != InputAction::Release;
			selector.wasDown = !selector.isDown && isDown;
			selector.isDown = isDown;
		}

		auto lastCursorSelect = cursorSelect;
		cursorSelect = nullptr;

		const auto size = Windows::Get()->GetWindow(0)->GetSize();
		objects.clear();

		auto viewMatrix = Matrix4::OrthographicMatrix(
			0.0f, size.x,
			0.0f, size.y, 
			-1.0f, 1.0f);

		canvas.GetConstraints().GetWidth()->SetOffset(size.x);
		canvas.GetConstraints().GetHeight()->SetOffset(size.y);

		UiObject* cursorSelect = nullptr;
		canvas.Update(viewMatrix, objects, cursorSelect);

		if (lastCursorSelect != cursorSelect)
		{
			Windows::Get()->GetWindow(0)->SetCursor(cursorSelect ? cursorSelect->GetCursorHover() : nullptr);
		}
	}

	bool Uis::IsDown(MouseButton button)
	{
		return selectors[button].isDown;
	}

	bool Uis::WasDown(MouseButton button)
	{
		return selectors[button].wasDown;
	}

	void Uis::CancelWasEvent(MouseButton button)
	{
		selectors[button].wasDown = false;
	}
}