#include <zae/Engine/Scene/Entity/EntityHolder.hpp>

namespace zae
{
	void EntityHolder::Update()
	{
		for (auto it = objects.begin(); it != objects.end();)
		{
			if ((*it)->IsRemoved())
			{
				it = objects.erase(it);
				continue;
			}

			(*it)->Update();
			++it;
		}
	}

	Entity* EntityHolder::GetEntity(const std::string& name) const
	{
		for (auto& object : objects)
		{
			if (object->GetName() == name)
				return object.get();
		}

		return nullptr;
	}

	Entity* EntityHolder::CreateEntity()
	{
		return objects.emplace_back(std::make_unique<Entity>()).get();
	}

	void EntityHolder::Add(std::unique_ptr<Entity>&& object)
	{
		objects.emplace_back(std::move(object));
	}

	void EntityHolder::Remove(Entity* object)
	{
		objects.erase(std::remove_if(objects.begin(), objects.end(), [object](const auto& e)
			{
				return e.get() == object;
			}), objects.end());
	}

	void EntityHolder::Move(Entity* object, EntityHolder& structure)
	{
		for (auto it = --objects.end(); it != objects.begin(); --it)
		{
			if ((*it).get() != object)
				continue;

			structure.Add(std::move(*it));
			objects.erase(it);
		}
	}

	void EntityHolder::Clear()
	{
		objects.clear();
	}

	std::vector<Entity*> EntityHolder::QueryAll()
	{
		std::vector<Entity*> entities;

		for (const auto& object : objects)
		{
			if (object->IsRemoved())
				continue;

			entities.emplace_back(object.get());
		}

		return entities;
	}

	std::vector<Entity*> EntityHolder::QueryByTag(const std::string& tag)
	{
		std::vector<Entity*> entities;

		for (const auto& object : objects)
		{
			if (object->IsRemoved() || (!tag.empty() && !object->HasTag(tag)))
			{
				continue;
			}

			entities.emplace_back(object.get());
		}

		return entities;
	}
	bool EntityHolder::Contains(Entity* object)
	{
		for (const auto& object2 : objects)
		{
			if (object2.get() == object)
				return true;
		}

		return false;
	}

}