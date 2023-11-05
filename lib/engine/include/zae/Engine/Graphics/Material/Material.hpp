#pragma once

#include <filesystem>
#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Core/Math/Colour.hpp>
#include <zae/Engine/Graphics/Images/Image2d.hpp>

namespace zae
{

	class Material : public Resource
	{
	public:
		static std::shared_ptr<Material> Create(std::filesystem::path filename, bool load = true);

		explicit Material(std::filesystem::path filename, bool load = true);
		~Material();

		std::type_index GetTypeIndex() const override { return typeid(Material); }

		const std::shared_ptr<Image2d>& GetDiffuseMap() { return diffuseMap; }
		void SetDiffuseMap(const std::shared_ptr<Image2d>& diffuseMap) { this->diffuseMap = diffuseMap; }

		const Colour& GetDiffuseColour() { return diffuseColour; }
		void SetDiffuseColour(const Colour& diffuseColour) { this->diffuseColour = diffuseColour; }

	private:
		void Load();

		std::shared_ptr<Image2d> diffuseMap;
		Colour diffuseColour;

		std::filesystem::path filename;
	};

}