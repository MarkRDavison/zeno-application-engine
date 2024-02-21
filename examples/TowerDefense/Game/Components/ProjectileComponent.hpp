#pragma once

#include <zae/Core/Math/Vector3.hpp>
#include <zae/Engine/Scene/Entity/Component.hpp>

class ProjectileComponent : public zae::Component
{
public:
	float speed; // TODO: Travel type, arc, direct etc
	zae::Entity* target{ nullptr };
	zae::Vector3f targetLastPosition;
};