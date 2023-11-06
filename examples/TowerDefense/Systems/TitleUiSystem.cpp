#include "TitleUiSystem.hpp"
#include <zae/Game/InputActionManager.hpp>
#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Components/TextComponent.hpp>
#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Core/Math/Rect.hpp>
#include "../Components/UiTextComponent.hpp"


TitleUiSystem::~TitleUiSystem()
{
	onTitleItemClicked.clearCallbacks();
}

void TitleUiSystem::Update(std::vector<zae::Entity*> entities)
{
	auto iam = zae::InputActionManager::Get();
	auto mousePos = zae::Windows::Get()->GetWindow(0)->GetMousePosition();
	auto size = zae::Windows::Get()->GetWindow(0)->GetSize();
	for (auto e : entities)
	{
		auto tf = e->GetComponent<zae::Transform>();
		auto text = e->GetComponent<zae::TextComponent>();
		auto uiTextComponent = e->GetComponent<UiTextComponent>();

		if (
			tf == nullptr ||
			text == nullptr ||
			uiTextComponent == nullptr ||
			!uiTextComponent->canInteract
		)
		{
			continue;
		}

		const auto& model = text->GetText()->GetModel();
		if (model)
		{
			const auto& minExtents = model->GetMinExtents();
			const auto& maxExtents = model->GetMaxExtents();

			zae::Vector4f position(minExtents.x, minExtents.y, 0.0f, 1.0f);
			
			auto offset = tf->GetPosition();

			zae::Rect r({ minExtents.x + offset.x, minExtents.y - offset.y }, { maxExtents.x - minExtents.x,maxExtents.y - minExtents.y });

			if (r.contains(mousePos))
			{
				if (uiTextComponent->hovered != true)
				{
					uiTextComponent->hovered = true;
					text->SetExternalColour(zae::Colour::Yellow);
				}

				if (iam->IsActionInvoked("CLICK"))
				{
					onTitleItemClicked.invoke(e->GetName());
				}
			}
			else
			{
				if (uiTextComponent->hovered != false)
				{
					uiTextComponent->hovered = false;
					text->SetExternalColour(zae::Colour::White);
				}
			}
		}
	}
}