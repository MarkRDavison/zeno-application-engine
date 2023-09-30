#pragma once

#include <zae/Engine/Scene/Entity/Component.hpp>
#include <zae/Core/Math/Matrix4.hpp>
#include <vector>

namespace zae
{

	class Transform : public Component
	{
	public:
		Transform(const Vector3f& position = {}, const Vector3f& rotation = {}, const Vector3f& scale = Vector3f(1.0f));
		~Transform();

		Matrix4 GetWorldMatrix() const;
		Vector3f GetPosition() const;
		Vector3f GetRotation() const;
		Vector3f GetScale() const;

		const Vector3f& GetLocalPosition() const { return position; }
		void SetLocalPosition(const Vector3f& localPosition) { position = localPosition; }

		const Vector3f& GetLocalRotation() const { return rotation; }
		void SetLocalRotation(const Vector3f& localRotation) { rotation = localRotation; }

		const Vector3f& GetLocalScale() const { return scale; }
		void SetLocalScale(const Vector3f& localScale) { scale = localScale; }

		Transform* GetParent() const { return parent; }
		void SetParent(Transform* parent);
		void SetParent(Entity* parent);

		const std::vector<Transform*>& GetChildren() const { return children; }

		bool operator==(const Transform& rhs) const;
		bool operator!=(const Transform& rhs) const;

		friend Transform operator*(const Transform& lhs, const Transform& rhs);

		Transform& operator*=(const Transform& rhs);

	private:
		const Transform* GetWorldTransform() const;

		void AddChild(Transform* child);
		void RemoveChild(Transform* child);

		Vector3f position;
		Vector3f rotation;
		Vector3f scale;

		Transform* parent = nullptr;
		std::vector<Transform*> children;
		mutable Transform* worldTransform = nullptr;
	};

}