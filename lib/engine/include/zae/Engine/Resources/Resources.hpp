#pragma once

#include <unordered_map>

#include <zae/Core/Utils/ThreadPool.hpp>
#include <zae/Engine/Engine.hpp>
#include <zae/Engine/Files.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>

#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Engine/Resources/ResourceNode.hpp>

namespace zae
{
	/**
	 * @brief Module used for managing resources. Resources are held alive as long as they are in use,
	 * a existing resource is queried by node value.
	 */
	class Resources
	{
		Resources();
		~Resources();

	public:

		static Resources* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new Resources();
			}
			return Instance;
		}

		void Update();

		std::shared_ptr<Resource> Find(const std::type_index& typeIndex, const ResourceNode& node) const;

		template<typename T>
		std::shared_ptr<T> Find(const ResourceNode& node) const
		{
			if (resources.find(typeid(T)) == resources.end())
			{
				return nullptr;
			}

			for (const auto& [key, resource] : resources.at(typeid(T)))
			{
				if (key == node)
				{
					return std::dynamic_pointer_cast<T>(resource);
				}
			}

			return nullptr;
		}

		void Add(const ResourceNode& node, const std::shared_ptr<Resource>& resource);
		void Remove(const std::shared_ptr<Resource>& resource);

		/**
		 * Gets the resource loader thread pool.
		 * @return The resource loader thread pool.
		 */
		ThreadPool& GetThreadPool() { return threadPool; }

	private:
		static Resources* Instance;
		std::unordered_map<std::type_index, std::map<ResourceNode, std::shared_ptr<Resource>>> resources;
		ElapsedTime elapsedPurge;

		ThreadPool threadPool;
	};
}

