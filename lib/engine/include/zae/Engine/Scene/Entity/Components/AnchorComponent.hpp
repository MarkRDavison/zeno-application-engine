#pragma once

#include <zae/Core/Utils/PositionAnchor.hpp>
#include <zae/Engine/Scene/Entity/Component.hpp>

namespace zae
{

	class AnchorComponent : public Component
	{
	public:
		PositionAnchor anchor;
	};

}