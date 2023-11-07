#pragma once

#include <zae/Engine/Graphics/Mesh/Mesh.hpp>

class MeshHelper
{
	MeshHelper() = delete;
public:
	static void RegisterMesh(const std::string& name, const std::string& path);
	static std::shared_ptr<zae::Mesh> LocateMesh(const std::string& name);

private:
	static std::unordered_map<std::string, std::string> namePaths;
};