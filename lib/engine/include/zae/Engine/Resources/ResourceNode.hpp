#pragma once

#include <string>
#include <zae/Core/Math/Math.hpp>

namespace zae
{

	class ResourceNode
	{
	public:
		explicit ResourceNode(std::string name, std::string filename) :
			name(std::move(name)),
			filename(std::move(filename))
		{

		}
		ResourceNode(std::string name) :
			name(std::move(name)),
			filename("")
		{

		}

		bool operator==(const ResourceNode& other) const
		{
			return this->name == other.name;
		}
		bool operator<(const ResourceNode& other) const
		{
			return this->name < other.name;
		}

		std::string filename;
		std::string name;
	};

}

namespace std
{
	template<>
	struct hash<zae::ResourceNode>
	{
		size_t operator()(const zae::ResourceNode& node) const noexcept
		{
			size_t seed = 0;
			zae::Math::HashCombine(seed, node.name);
			zae::Math::HashCombine(seed, node.filename);
			return seed;
		}
	};
}