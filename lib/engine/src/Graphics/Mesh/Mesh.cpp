#include <zae/Engine/Graphics/Mesh/Mesh.hpp>

#include <zae/Engine/Graphics/Material/Material.hpp>
#include <zae/Engine/Files.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Core/Utils/String.hpp>

#include <cassert>

namespace zae
{

	struct GeometryResourceInstance
	{
		std::vector<Vertex3d> vertices3d;
		std::vector<uint32_t> indices;

		Vector3f center{};
		Vector3f minExtents{};
		Vector3f maxExtents{};

		std::string name;
		std::string materialName;

	};

	// TODO: Move
	struct MaterialResourceData
	{
		std::string name;
		//std::string shaderName;
		//bool autoRelease;
		Colour diffuseColour;
		//std::string diffuseMapName;
		//std::string specularMapName;
		//std::string normalMapName;
		//float shininess;
	};
	struct MeshVertexIndexData
	{
		uint32_t positionIndex;
		uint32_t normalIndex;
		uint32_t texCoordIndex;
	};

	struct MeshFaceData
	{
		MeshVertexIndexData vertices[3];
	};

	struct MeshGroupData
	{
		std::vector<MeshFaceData> faces;
	};

	void processSubOject(
		std::vector<Vector3f>& _positions,
		std::vector<Vector3f>& _normals,
		std::vector<Vector2f>& _texCoords,
		std::vector<MeshFaceData>& _faces,
		GeometryResourceInstance& _data
	)
	{
		bool extentSet = false;
		bool skipNormals = false;
		bool skipTexCoords = false;

		const auto faceCount = _faces.size();
		const auto normalCount = _normals.size();
		const auto texCoordCount = _texCoords.size();

		if (normalCount == 0)
		{
			Log::Warning("No normals are present in this model.", '\n');
			skipNormals = true;
		}

		if (texCoordCount == 0)
		{
			Log::Warning("No tex coords are present in this model.", '\n');
			skipTexCoords = true;
		}

		for (uint32_t f = 0; f < _faces.size(); ++f)
		{
			auto& face = _faces[f];
			for (uint64_t i = 0; i < 3; ++i)
			{
				auto& indexData = face.vertices[i];
				_data.indices.push_back(i + (f * 3));

				auto& vert = _data.vertices3d.emplace_back();

				auto pos = _positions[indexData.positionIndex - 1]; // Obj is one indexed
				vert.position = pos;

				// min extends
				if (pos.x < _data.minExtents.x || !extentSet)
				{
					_data.minExtents.x = pos.x;
				}
				if (pos.y < _data.minExtents.y || !extentSet)
				{
					_data.minExtents.y = pos.y;
				}
				if (pos.z < _data.minExtents.z || !extentSet)
				{
					_data.minExtents.z = pos.z;
				}

				// max extends
				if (pos.x > _data.maxExtents.x || !extentSet)
				{
					_data.maxExtents.x = pos.x;
				}
				if (pos.y > _data.maxExtents.y || !extentSet)
				{
					_data.maxExtents.y = pos.y;
				}
				if (pos.z > _data.maxExtents.z || !extentSet)
				{
					_data.maxExtents.z = pos.z;
				}

				extentSet = true;

				if (skipNormals)
				{
					vert.normal = { 0.0f, 0.0f, 1.0f };
				}
				else
				{
					vert.normal = _normals[indexData.normalIndex - 1];
				}

				if (skipTexCoords)
				{
					vert.uv = { 0.0f, 0.0f };
				}
				else
				{
					vert.uv = _texCoords[indexData.texCoordIndex - 1];
				}

				// TODO: Hardcoded to white for now
				// vert.colour = { 1.0f, 1.0f, 1.0f, 1.0f };
			}
		}

		_data.center.x = (_data.minExtents.x + _data.maxExtents.x) / 2.0f;
		_data.center.y = (_data.minExtents.y + _data.maxExtents.y) / 2.0f;
		_data.center.z = (_data.minExtents.z + _data.maxExtents.z) / 2.0f;
	}

	void CreateMaterial(const MaterialResourceData& materialResourceData)
	{
		auto mat = std::make_shared<Material>("", false);
		mat->SetDiffuseMap(Resources::Get()->Find<Image2d>(ResourceNode("DEFAULT")));
		mat->SetDiffuseColour(materialResourceData.diffuseColour);

		Resources::Get()->Add(ResourceNode(materialResourceData.name), mat);

		Log::Info("Created Material: ", materialResourceData.name, '\n');
	}

	bool importObjMaterialLibraryFile(
		const std::string& _mtlFilename
	)
	{
		// TODO: Option to load all at once or read line by line
		auto fileLoaded = Files::Read(_mtlFilename);

		if (!fileLoaded.has_value())
		{
			Log::Error("Mesh file could not be loaded: ", _mtlFilename, '\n');
			return false;
		}

		MaterialResourceData currentConfig{};

		bool hitName = false;
		for (const auto& l : String::Split(fileLoaded.value(), '\n'))
		{
			const auto line = String::Trim(l);

			if (line.empty()) { continue; }

			const char firstChar = tolower(line[0]);

			switch (firstChar)
			{
				case '#':
					continue;
				case 'k':
				{
					const char secondChar = tolower(line[1]);
					switch (secondChar)
					{
						case 'a': // ambient
						case 'd': // diffuse
						{
							const auto& parts = String::Split(std::string(line), ' ');
							assert(parts.size() == 4);
							currentConfig.diffuseColour.r = std::stof(parts[1]);
							currentConfig.diffuseColour.g = std::stof(parts[2]);
							currentConfig.diffuseColour.b = std::stof(parts[3]);
							currentConfig.diffuseColour.a = 1.0f;
							break;
						}
						default:
						{
							Log::Warning("Unhandled material file line: ", line, '\n');
							break;
						}
					}
					break;
				}
				case 'n':
				{
					const auto& parts = String::Split(std::string(line), ' ');
					assert(parts.size() == 2);

					if (!currentConfig.name.empty())
					{
						CreateMaterial(currentConfig);

						currentConfig = {};
					}

					currentConfig.name = parts[1];

					break;
				}
				default:
				{
					Log::Warning("Unhandled material file line: ", line, '\n');
					break;
				}
			}
		}

		if (!currentConfig.name.empty())
		{
			// Same
			CreateMaterial(currentConfig);
		}

		return true;
	}

	std::shared_ptr<Mesh> Mesh::Create(std::filesystem::path filename, bool load /*= true*/)
	{
		auto node = ResourceNode(filename.string(), filename.string());
		if (auto resource = Resources::Get()->Find<Mesh>(node))
		{
			return resource;
		}

		auto result = std::make_shared<Mesh>(filename, load);
		Resources::Get()->Add(node, std::dynamic_pointer_cast<Resource>(result));
		return result;
	}

	Mesh::Mesh(std::filesystem::path filename, bool load /*= true*/) :
		filename(filename)
	{
		if (load)
		{
			Load();
		}
	}
	Mesh::~Mesh()
	{

	}

	void Mesh::Load()
	{
		if (filename.empty()) return;

		if (!filename.string().ends_with(".obj"))
		{
			Log::Error("Mesh file not of supported type (.obj): ", filename, '\n');
			return;
		}

#ifdef ZAE_DEBUG
		auto debugStart = Time::Now();
#endif

		// TODO: Option to load all at once or read line by line
		auto fileLoaded = Files::Read(filename);

		if (!fileLoaded.has_value())
		{
			Log::Error("Mesh file could not be loaded: ", filename, '\n');
			return;
		}

		std::vector<GeometryResourceInstance>  geometries;

		std::vector<Vector3f> positions; // TODO: PERF: Reserve  16834
		std::vector<Vector3f> normals; // TODO: PERF: Reserve  16834
		std::vector<Vector2f> texCoords; // TODO: PERF: Reserve  16834
		std::vector<MeshGroupData> groups;// TODO: PERF: Reserve  4

		positions.reserve(16384);
		normals.reserve(16384);
		texCoords.reserve(16384);
		groups.reserve(4);

		std::string name;
		std::string materialName;
		std::vector<std::string> materialNames;
		char previousStartingCharacters[2] = { 0,0 };

		for (const auto& line : String::Split(fileLoaded.value(), '\n'))
		{
			if (line.empty()) { continue; }

			const char firstChar = line[0];
			switch (firstChar)
			{
				case '#':
				{
					// Comment
					continue;
				}
				case 'o':
				{
					const auto& parts = String::Split(line, ' ');
					assert(parts.size() == 2);
					name = parts[1];
					break;
				}
				case 'v':
				{
					const char secondChar = line[1];

					switch (secondChar)
					{
						case ' ':
						{
							// Vertex position

							const auto& parts = String::Split(line, ' ');
							assert(parts.size() == 4);
							positions.push_back(Vector3f(
								std::stof(parts[1]),
								std::stof(parts[2]),
								std::stof(parts[3])
							));
							break;
						}
						case 'n':
						{
							// Vertex normal
							const auto& parts = String::Split(line, ' ');
							assert(parts.size() == 4);
							normals.push_back(Vector3f(
								std::stof(parts[1]),
								std::stof(parts[2]),
								std::stof(parts[3])
							));
							break;
						}
						case 't':
						{
							// Vertex tex coord
							const auto& parts = String::Split(line, ' ');
							assert(parts.size() == 3);
							texCoords.push_back(Vector2f(
								std::stof(parts[1]),
								std::stof(parts[2])
							));
							break;
						}
					}
					break;
				}
				case 's':
				{
					break;
				}
				case 'f':
				{
					// Face
					const auto& parts = String::Split(line, " /");
					assert(parts.size() == 10);
					MeshFaceData face;
					const auto normalCount = normals.size();
					const auto texCoordCount = texCoords.size();

					if (normalCount == 0 || texCoordCount == 0)
					{
						// obj doesnt have normals and/or textures
						face.vertices[0].positionIndex = (uint32_t)std::stol(parts[1]);
						face.vertices[1].positionIndex = (uint32_t)std::stol(parts[4]);
						face.vertices[2].positionIndex = (uint32_t)std::stol(parts[7]);
					}
					else
					{
						face.vertices[0].positionIndex = (uint32_t)std::stol(parts[1]);
						face.vertices[0].texCoordIndex = (uint32_t)std::stol(parts[2]);
						face.vertices[0].normalIndex = (uint32_t)std::stol(parts[3]);
						face.vertices[1].positionIndex = (uint32_t)std::stol(parts[4]);
						face.vertices[1].texCoordIndex = (uint32_t)std::stol(parts[5]);
						face.vertices[1].normalIndex = (uint32_t)std::stol(parts[6]);
						face.vertices[2].positionIndex = (uint32_t)std::stol(parts[7]);
						face.vertices[2].texCoordIndex = (uint32_t)std::stol(parts[8]);
						face.vertices[2].normalIndex = (uint32_t)std::stol(parts[9]);
					}
					auto& group = groups.back();
					group.faces.push_back(face);
					break;
				}
				case 'm':
				{
					// Material library file
					const auto& parts = String::Split(line, " /");
					assert(parts.size() == 2);
					assert(parts[0] == "mtllib");
					materialName = parts[1];
					break;
				}
				case 'u':
				{
					// New group
					auto& newGroup = groups.emplace_back();
					newGroup.faces.reserve(16384);
					// TODO: PERF: reserve newGroup.faces
					const auto& parts = String::Split(line, " /");
					assert(parts.size() == 2);
					materialNames.push_back(parts[1]);
					break;
				}
				case 'g':
				{
					auto groupCount = groups.size();
					for (auto i = 0; i < groupCount; ++i)
					{
						auto& newData = geometries.emplace_back();
						newData.name = name;

						if (i > 0)
						{
							newData.name += std::to_string(i);
						}
						newData.materialName = materialNames[i];

						processSubOject(positions, normals, texCoords, groups[i].faces, newData);

						groups[i].faces.clear(); // cleaning up
						materialNames[i].clear(); // TODO: This is the issue?
					}

					for (auto i = 0; i < groupCount; ++i)
					{
						materialNames.erase(materialNames.begin());
					}
					groups.clear();
					name.clear();

					const auto& parts = String::Split(line, " /");
					assert(parts.size() == 2);

					name = parts[1];

					break;
				}
			}

			previousStartingCharacters[1] = previousStartingCharacters[0];
			previousStartingCharacters[0] = firstChar;
		}

		// TODO: Reuse, copied from above
		auto groupCount = groups.size();
		for (auto i = 0; i < groupCount; ++i)
		{
			auto& newData = geometries.emplace_back();
			newData.name = name;

			if (i > 0)
			{
				newData.name += std::to_string(i);
			}
			newData.materialName = materialNames[i];

			processSubOject(positions, normals, texCoords, groups[i].faces, newData);

			groups[i].faces.clear(); // cleaning up
			materialNames[i].clear();
		}

		for (auto i = 0; i < groupCount; ++i)
		{
			materialNames.erase(materialNames.begin());
		}

		groups.clear();
		positions.clear();
		normals.clear();
		texCoords.clear();

		if (!materialName.empty())
		{
			// 1:54:43
			auto modelDir = filename.string().substr(0, filename.string().find_last_of("/") + 1);
			auto fullMaterialPath = modelDir + materialName;
			if (!importObjMaterialLibraryFile(fullMaterialPath))
			{
				Log::Error("Error reading obj material file.", '\n');
			}
		}

		for (const auto& geom : geometries)
		{
			auto& model = models.emplace_back(std::make_shared<Model>(geom.vertices3d, geom.indices));
			model->SetMaterial(Resources::Get()->Find<Material>(ResourceNode(geom.materialName)));
		}

#ifdef ZAE_DEBUG
		Log::Out("Mesh ", filename, " loaded in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif
	}

}