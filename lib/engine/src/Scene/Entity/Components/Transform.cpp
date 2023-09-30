#include <zae/Engine/Scene/Entity/Components/Transform.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>

namespace zae
{
	Transform::Transform(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale) :
		position(position),
		rotation(rotation),
		scale(scale)
	{
	}

	Transform::~Transform()
	{
		delete worldTransform;

		for (auto& child : children)
		{
			child->parent = nullptr;
		}

		if (parent)
		{
			parent->RemoveChild(this);
		}
	}

	Matrix4 Transform::GetWorldMatrix() const
	{
		auto worldTransform = GetWorldTransform();
		return Matrix4::TransformationMatrix(worldTransform->position, worldTransform->rotation, worldTransform->scale);
	}

	Vector3f Transform::GetPosition() const
	{
		return GetWorldTransform()->position;
	}

	Vector3f Transform::GetRotation() const
	{
		return GetWorldTransform()->rotation;
	}

	Vector3f Transform::GetScale() const
	{
		return GetWorldTransform()->scale;
	}

	void Transform::SetParent(Transform* parent)
	{
		if (parent)
		{
			parent->RemoveChild(this);
		}

		this->parent = parent;

		if (parent)
		{
			parent->AddChild(this);
		}
	}

	void Transform::SetParent(Entity* parent)
	{
		SetParent(parent->GetComponent<Transform>());
	}

	const Transform* Transform::GetWorldTransform() const
	{
		if (!parent)
		{
			if (worldTransform)
			{
				delete worldTransform;
				worldTransform = nullptr;
			}

			return this;
		}

		if (!worldTransform)
		{
			worldTransform = new Transform();
		}

		*worldTransform = *parent->GetWorldTransform() * *this;
		return worldTransform;
	}

	void Transform::AddChild(Transform* child)
	{
		children.emplace_back(child);
	}

	void Transform::RemoveChild(Transform* child)
	{
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	bool Transform::operator==(const Transform& rhs) const
	{
		return position == rhs.position && rotation == rhs.rotation && scale == rhs.scale;
	}

	bool Transform::operator!=(const Transform& rhs) const
	{
		return !operator==(rhs);
	}

	Transform operator*(const Transform& lhs, const Transform& rhs)
	{
		return { Vector3f(lhs.GetWorldMatrix().Transform(Vector4f(rhs.position))), lhs.rotation + rhs.rotation, lhs.scale * rhs.scale };
	}

	Transform& Transform::operator*=(const Transform& rhs)
	{
		return *this = *this * rhs;
	}
}