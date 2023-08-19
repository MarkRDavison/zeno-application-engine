#include <zae/Engine/Graphics/Bitmaps/Bitmap.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

#include <zae/Core/Log.hpp>
#include <zae/Engine/Files.hpp>

namespace zae
{
	Bitmap::Bitmap(std::filesystem::path filename) :
		filename(std::move(filename))
	{
		Load(this->filename);
	}

	Bitmap::Bitmap(const Vector2ui& size, uint32_t bytesPerPixel) :
		data(std::make_unique<uint8_t[]>(CalculateLength(size, bytesPerPixel))),
		size(size),
		bytesPerPixel(bytesPerPixel)
	{
	}

	Bitmap::Bitmap(std::unique_ptr<uint8_t[]>&& data, const Vector2ui& size, uint32_t bytesPerPixel) :
		data(std::move(data)),
		size(size),
		bytesPerPixel(bytesPerPixel)
	{
	}

	void Bitmap::Load(const std::filesystem::path& filename)
	{
		auto fileLoaded = Files::ReadBytes(filename);

		if (fileLoaded.empty())
		{
			Log::Error("Bitmap could not be loaded: ", filename, '\n');
			return;
		}

		// TODO: This needs improving
		data = std::unique_ptr<uint8_t[]>(stbi_load_from_memory(reinterpret_cast<uint8_t*>(fileLoaded.data()), static_cast<uint32_t>(fileLoaded.size()),
			reinterpret_cast<int32_t*>(&size.x), reinterpret_cast<int32_t*>(&size.y), reinterpret_cast<int32_t*>(&bytesPerPixel), STBI_rgb_alpha));
		bytesPerPixel = 4;
	}

	void Bitmap::Write(const std::filesystem::path& filename) const
	{
		if (auto parentPath = filename.parent_path(); !parentPath.empty())
			std::filesystem::create_directories(parentPath);

		//Registry()[filename.extension().string()].second(*this, filename);

		std::ofstream os(filename, std::ios::binary | std::ios::out);
		int32_t len;
		std::unique_ptr<uint8_t[]> png(stbi_write_png_to_mem(data.get(), size.x * bytesPerPixel, size.x, size.y, bytesPerPixel, &len));
		os.write(reinterpret_cast<char*>(png.get()), len);
	}

	uint32_t Bitmap::GetLength() const
	{
		return size.x * size.y * bytesPerPixel;
	}

	uint32_t Bitmap::CalculateLength(const Vector2ui& size, uint32_t bytesPerPixel)
	{
		return size.x * size.y * bytesPerPixel;
	}
}
