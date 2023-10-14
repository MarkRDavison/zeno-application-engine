#pragma once

#include <zae/Engine/Devices/Windows.hpp>
#include <zae/Core/Math/Vector2.hpp>
#include <zae/Core/Math/Vector4.hpp>
#include <zae/Core/Math/Matrix4.hpp>

namespace zae
{

	class UiObject
	{
	public:
		UiObject();
		virtual ~UiObject();

		void Update(const Matrix4& viewMatrix, std::vector<UiObject*>& list, UiObject*& cursorSelect);

		virtual void UpdateObject();

		const std::vector<UiObject*>& GetChildren() const { return children; }

		virtual void AddChild(UiObject* child);

		virtual void RemoveChild(UiObject* child);

		void ClearChildren();

		UiObject* GetParent() const { return parent; }

		void SetParent(UiObject* parent);

		bool IsEnabled() const;
		void SetEnabled(bool enabled) { this->enabled = enabled; }

	private:
		std::vector<UiObject*> children;
		UiObject* parent = nullptr;

		bool enabled = true;

	};

}