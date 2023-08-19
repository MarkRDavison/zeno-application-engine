#pragma once

#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace zae
{
	using TypeId = std::size_t;

	template<typename T>
	class TypeInfo
	{
	public:
		TypeInfo() = delete;

		static std::unordered_map<std::type_index, TypeId>& GetTypeCache()
		{
			static std::unordered_map<std::type_index, TypeId> instance;
			return instance;
		}
		static TypeId& GetnextTypeId()
		{
			static TypeId nextTypeId = 0;
			return nextTypeId;
		}

		/**
		 * Get the type ID of K which is a base of T.
		 * @tparam K The type ID K.
		 * @return The type ID.
		 */
		template<typename K,
			typename = std::enable_if_t<std::is_convertible_v<K*, T*>>>
		static TypeId GetTypeId() noexcept
		{
			std::type_index typeIndex(typeid(K));

			auto& typeMap = GetTypeCache();

			if (auto it = typeMap.find(typeIndex); it != typeMap.end())
			{
				return it->second;
			}

			const auto id = NextTypeId();
			typeMap[typeIndex] = id;
			return id;
		}

	private:
		static TypeId NextTypeId() noexcept
		{
			auto& nextTypeId = GetnextTypeId();
			const auto id = nextTypeId;
			++nextTypeId;
			return id;
		}
	};
}