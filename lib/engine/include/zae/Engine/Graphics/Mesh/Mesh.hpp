#pragma once

#include <filesystem>
#include <zae/Core/Math/Vector3.hpp>
#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Engine/Graphics/Models/Vertex3d.hpp>
#include <zae/Engine/Graphics/Models/Model.hpp>

namespace zae
{

	class Mesh : public Resource
	{
	public:
		static std::shared_ptr<Mesh> Create(std::filesystem::path filename, bool load = true);

		explicit Mesh(std::filesystem::path filename, bool load = true);
		~Mesh();

		std::type_index GetTypeIndex() const override { return typeid(Mesh); }

		const std::vector<std::shared_ptr<Model>>& GetModels() const { return models; }

	private:
		void Load();

		std::filesystem::path filename;

		std::vector<std::shared_ptr<Model>> models;
	};

}