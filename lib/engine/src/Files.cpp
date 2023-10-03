#include <zae/Engine/Files.hpp>

#include <iterator>
#include <zae/Core/Config.hpp>
#include <zae/Core/Log.hpp>

namespace zae
{
	using std::streambuf;
	using std::ios_base;

	Files* Files::Instance = nullptr;

	Files::Files()
	{
		// TODO: Get from Engine -> argv[0]
		if (std::filesystem::exists(ZAE_RESOURCES_DEV))
		{
			AddSearchPath(std::string(ZAE_RESOURCES_DEV));
		}
		if (std::filesystem::exists(ZAE_RESOURCES_DEV_LAPTOP))
		{
			AddSearchPath(std::string(ZAE_RESOURCES_DEV_LAPTOP));
		}
	}

	Files::~Files()
	{
	}

	void Files::Update()
	{

	}

	void Files::AddSearchPath(const std::string& path)
	{
		if (std::find(searchPaths.begin(), searchPaths.end(), path) != searchPaths.end())
		{
			return;
		}

		if (!std::filesystem::exists(path))
		{
			Log::Warning("Search path does not exist: ", path, '\n');
			return;
		}

		searchPaths.emplace_back(path);
	}

	void Files::RemoveSearchPath(const std::string& path)
	{
		auto it = std::find(searchPaths.begin(), searchPaths.end(), path);

		if (it == searchPaths.end())
		{
			return;
		}

		searchPaths.erase(it);
	}

	void Files::ClearSearchPath()
	{
		searchPaths.clear();
	}

	bool Files::ExistsInPath(const std::filesystem::path& path)
	{
		const auto searchPaths = Files::Get()->searchPaths;
		auto pathStr = path.string();
		std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
		return std::filesystem::exists(pathStr);// TODO: Better validation && std::find(searchPaths.begin(), searchPaths.end(), pathStr) != searchPaths.end();
	}


	std::optional<std::string> Files::GetQualifiedPath(const std::filesystem::path& path)
	{
		const auto searchPaths = Files::Get()->searchPaths;
		for (const auto& searchPath : searchPaths)
		{
			auto pathStr = searchPath + "/" + path.string();
			if (std::filesystem::exists(pathStr))
			{
				return pathStr;
			}
		}

		return {};
	}

	std::optional<std::string> Files::Read(const std::filesystem::path& path)
	{
		const auto searchPaths = Files::Get()->searchPaths;
		for (const auto& searchPath : searchPaths)
		{
			auto pathStr = searchPath + "/" + path.string();
			std::ifstream file;
			file.open(pathStr);

			if (!file.good())
			{
				Log::Error("Failed to open file ", path, '\n');
				continue;
			}

			std::string str;

			file.seekg(0, std::ios::end);
			str.reserve(static_cast<unsigned int>(file.tellg()));
			file.seekg(0, std::ios::beg);

			str.insert(str.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

			file.close();

			return str;
		}

		return std::nullopt;
	}

	std::vector<unsigned char> Files::ReadBytes(const std::filesystem::path& path)
	{
		const auto searchPaths = Files::Get()->searchPaths;
		for (const auto& searchPath : searchPaths)
		{
			auto pathStr = searchPath + "/" + path.string();

			std::ifstream file{ pathStr, std::ios::ate | std::ios::binary };
			if (!file.is_open())
			{
				continue;
			}

			size_t fileSize = static_cast<size_t>(file.tellg());
			std::vector<unsigned char> buffer(fileSize);

			file.seekg(0);
			file.read((char*)buffer.data(), fileSize);

			file.close();
			return buffer;
		}

		Log::Error("Failed to open file ", path, '\n');
		return {};
	}

	std::vector<std::string> Files::FilesInPath(const std::filesystem::path& path, bool recursive)
	{
		auto pathStr = path.string();
		std::replace(pathStr.begin(), pathStr.end(), '\\', '/');

		std::vector<std::string> files;

		for (const auto& i : std::filesystem::directory_iterator(pathStr))
		{
			if (std::filesystem::is_directory(i))
			{
				if (recursive)
				{
					const auto& recursiveFiles = FilesInPath(i.path());
					files.insert(files.end(), recursiveFiles.begin(), recursiveFiles.end());
				}
			}
			else
			{
				files.push_back(i.path().string());
			}
		}

		return files;
	}

	std::istream& Files::SafeGetLine(std::istream& is, std::string& t)
	{
		t.clear();

		// The characters in the stream are read one-by-one using a std::streambuf.
		// That is faster than reading them one-by-one using the std::istream.
		// Code that uses streambuf this way must be guarded by a sentry object.
		// The sentry object performs various tasks,
		// such as thread synchronization and updating the stream state.

		std::istream::sentry se(is, true);
		auto sb = is.rdbuf();

		if (se)
		{
			while (true)
			{
				auto c = sb->sbumpc();

				switch (c)
				{
				case '\n':
					return is;
				case '\r':
					if (sb->sgetc() == '\n')
						sb->sbumpc();
					return is;
				case EOF:
					// Also handle the case when the last line has no line ending
					if (t.empty())
						is.setstate(std::ios::eofbit);

					return is;
				default:
					t += static_cast<char>(c);
				}
			}
		}

		return is;
	}
}
