#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Scene/Entity/Component.hpp>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>

namespace zae
{

	class Entity final : NonCopyable
	{
	public:
		Entity() = default;

		void Update();

		const std::string& GetName() const { return name; }
		void SetName(const std::string& name) { this->name = name; }

		void AddTag(const std::string& tag);
		void ClearTag(const std::string& tag);
		bool HasTag(const std::string& tag) const;

		bool IsRemoved() const { return removed; }
		void SetRemoved(bool removed) { this->removed = removed; }

		void RemoveComponent(Component* component);

		Component* AddComponent(std::unique_ptr<Component>&& component);

		const std::vector<std::unique_ptr<Component>>& GetComponents() const { return components; }
		uint32_t GetComponentCount() const { return static_cast<uint32_t>(components.size()); }

		template<typename T>
		T* GetComponent(bool allowDisabled = false) const
		{
			T* alternative = nullptr;

			for (const auto& component : components)
			{
				auto casted = dynamic_cast<T*>(component.get());

				if (casted)
				{
					if (allowDisabled && !component->IsEnabled())
					{
						alternative = casted;
						continue;
					}

					return casted;
				}
			}

			return alternative;
		}

		template<typename... Args>
		bool HasComponents(bool allowDisabled = false) const
		{
			return (HasComponent<Args>(allowDisabled) && ...);
		}

		template<typename T>
		bool HasComponent(bool allowDisabled = false) const
		{
			const auto c =  GetComponent<T>(allowDisabled);
			return c != nullptr && (allowDisabled || c->IsEnabled());
		}

		template<typename T>
		std::vector<T*> GetComponents(bool allowDisabled = false) const
		{
			std::vector<T*> components;

			for (const auto& component : this->components)
			{
				auto casted = dynamic_cast<T*>(component.get());

				if (casted)
				{
					if (allowDisabled && !component->IsEnabled())
					{
						components.emplace_back(casted);
						continue;
					}

					components.emplace_back(casted);
				}
			}

			return components;
		}

		template<typename T, typename... Args>
		T* AddComponent(Args &&... args)
		{
			return dynamic_cast<T*>(AddComponent(std::make_unique<T>(std::forward<Args>(args)...)));
		}

		template<typename T>
		void RemoveComponent()
		{
			for (int i = 0; i < (int)components.size(); ++i)
			{
				auto casted = dynamic_cast<T*>(components[i].get());

				if (casted)
				{
					components[i]->SetEntity(nullptr);
					components.erase(components.begin() + i);
					i--;
				}
			}
		}



	private:
		std::string name;
		bool removed = false;
		std::vector<std::unique_ptr<Component>> components;
		std::unordered_set<std::size_t> tags;
	};

}