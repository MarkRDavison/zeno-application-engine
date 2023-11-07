#include "MeshHelper.hpp"
#include <zae/Engine/Resources/Resources.hpp>

std::unordered_map<std::string, std::string> MeshHelper::namePaths = {};

void MeshHelper::RegisterMesh(const std::string& name, const std::string& path) 
{
	namePaths[name] = path;
}

std::shared_ptr<zae::Mesh> MeshHelper::LocateMesh(const std::string& name)
{
	return zae::Resources::Get()->GetOrAdd<zae::Mesh>(zae::ResourceNode(name, namePaths.at(name)));
}