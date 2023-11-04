#include <zae/Engine/Graphics/Material/Material.hpp>

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Core/Utils/String.hpp>

namespace zae
{

	std::shared_ptr<Material> Material::Create(std::filesystem::path filename, bool load /*= true*/)
	{
		auto node = ResourceNode(filename.string(), filename.string());
		if (auto resource = Resources::Get()->Find<Material>(node))
		{
			return resource;
		}

		auto result = std::make_shared<Material>(filename, load);
		Resources::Get()->Add(node, std::dynamic_pointer_cast<Resource>(result));
		return result;
	}

	Material::Material(std::filesystem::path filename, bool load /*= true*/) :
		filename(filename)
	{
		if (load)
		{
			Load();
		}
	}
	Material::~Material()
	{

	}

	void Material::Load()
	{
		if (filename.empty()) return;

#ifdef ZAE_DEBUG
		auto debugStart = Time::Now();
#endif

		// TODO: Option to load all at once or read line by line
		auto fileLoaded = Files::Read(filename);

		if (!fileLoaded.has_value())
		{
			Log::Error("Material file could not be loaded: ", filename, '\n');
			return;
		}



#ifdef ZAE_DEBUG
		Log::Out("Material ", filename, " loaded in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif

	}
}