#pragma once

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

namespace zae
{

	class System : NonCopyable
	{
	public:
		System(EntityHolder* entities) : entities(entities) {}
		virtual ~System() = default;

		virtual void Update() {
			Update(entities->QueryByTag(tag));
		}

		virtual void Update(std::vector<Entity*> entities) = 0;

		bool IsEnabled() const { return enabled; }
		void SetEnabled(bool enable) { this->enabled = enable; }

		void SetQueryTag(const std::string& tag) { this->tag = tag; }
		void ClearQueryTag() { this->tag = {}; }

	protected:
		EntityHolder* entities;
		std::string tag;
	private:
		bool enabled = true;

	};

	template <typename... Args>
	class ComponentSystem : public System
	{
	public:
		ComponentSystem(EntityHolder* entities) : System(entities) {}
		virtual ~ComponentSystem() = default;

		void Update(std::vector<Entity*> entities) override = 0;

		void Update() override
		{
			std::vector<Entity*> es;

			for (auto e : entities->QueryByTag(tag))
			{
				if (e->HasComponents<Args...>())
				{
					es.push_back(e);
				}
			}

			Update(es);
		}
	};

}