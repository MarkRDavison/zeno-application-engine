#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Scene/Entity/Entity.hpp>

namespace zae
{

	class EntityHolder : NonCopyable
	{
	public:
		EntityHolder() = default;

		void Update();
		Entity* GetEntity(const std::string& name) const;
		Entity* CreateEntity();
		void Add(std::unique_ptr<Entity>&& object);
		void Remove(Entity* object);
		void Move(Entity* object, EntityHolder& structure);
		void Clear();
		uint32_t GetSize() const { return static_cast<uint32_t>(objects.size()); }
		std::vector<Entity*> QueryAll();

		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, Component*>>>
		T* GetComponent(bool allowDisabled = false)
		{
			for (auto it = objects.begin(); it != objects.end(); ++it)
			{
				auto component = (*it)->GetComponent<T>();

				if (component && (component->IsEnabled() || allowDisabled))
				{
					return component;
				}
			}

			return nullptr;
		}

		template<typename T,
			typename = std::enable_if_t<std::is_convertible_v<T*, Component*>>>
		std::vector<T*> QueryComponents(bool allowDisabled = false)
		{
			std::vector<T*> components;

			for (auto it = objects.begin(); it != objects.end(); ++it)
			{
				for (const auto& component : (*it)->GetComponents<T>())
				{
					if (component && (component->IsEnabled() || allowDisabled))
					{
						components.emplace_back(component);
					}
				}
			}

			return components;
		}

		bool Contains(Entity* object);

	private:
		std::vector<std::unique_ptr<Entity>> objects;
	};

}