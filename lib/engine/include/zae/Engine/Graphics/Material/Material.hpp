#pragma once

#include <filesystem>
#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Core/Math/Colour.hpp>

namespace zae
{

	class Material : public Resource
	{
	public:
		static std::shared_ptr<Material> Create(std::filesystem::path filename, bool load = true);

		explicit Material(std::filesystem::path filename, bool load = true);
		~Material();

		std::type_index GetTypeIndex() const override { return typeid(Material); }

		const std::string& GetDiffuseMap() { return diffuseMapName; }
		void SetDiffuseMap(const std::string& diffuseMapName) { this->diffuseMapName = diffuseMapName; }

		const Colour& GetDiffuseColour() { return diffuseColour; }
		void SetDiffuseColour(const Colour& diffuseColour) { this->diffuseColour = diffuseColour; }

	private:
		void Load();

		std::string diffuseMapName;
		Colour diffuseColour;

		std::filesystem::path filename;
	};

}