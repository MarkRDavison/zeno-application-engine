#pragma once

#include <vector>
#include <zae/Engine/Scene/Entity/System.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>
#include <zae/Core/Utils/Signal.hpp>

class TitleUiSystem : public zae::System
{
public:
	TitleUiSystem(zae::EntityHolder* entities);
	~TitleUiSystem();

	void Update(std::vector<zae::Entity*> entities) override;

	zae::Signal<std::string> onTitleItemClicked;
};