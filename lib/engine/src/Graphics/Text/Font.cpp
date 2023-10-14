#include <zae/Engine/Graphics/Text/Font.hpp>

#define FT_CONFIG_OPTION_ERROR_STRINGS
#include <ft2build.h>
#include FT_FREETYPE_H

#include <zae/Engine/Files.hpp>
#include <zae/Engine/Resources/Resources.hpp>
#include <zae/Engine/Graphics/Graphics.hpp>

namespace zae
{
	static const std::wstring_view CHARACTERS = L" \t\r\nABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890\"!`?'.,;:()[]{}<>|/@\\^$-%+=#_&~*";

	template<typename T>
	constexpr double F26DOT6_TO_DOUBLE(T x)
	{
		return 1.0 / 64.0 * double(x);
	}

	std::shared_ptr<Font> Font::Create(std::filesystem::path filename, std::size_t size, bool load)
	{
		auto node = ResourceNode(filename.string(), filename.string());
		if (auto resource = Resources::Get()->Find<Font>(node))
		{
			return resource;
		}


		auto result = std::make_shared<Font>(filename, size, load);
		Resources::Get()->Add(node, std::dynamic_pointer_cast<Resource>(result));
		return result;
	}

	Font::Font(std::filesystem::path filename, std::size_t size, bool load) :
		filename(std::move(filename)),
		size(size)
	{
		if (load)
		{
			Load();
		}
	}

	Font::~Font()
	{
		Close();
	}

	std::optional<Font::Glyph> Font::GetGlyph(wchar_t ascii) const
	{
		auto it = indices.find(ascii);

		if (it != indices.end())
		{
			return glyphs[it->second];
		}

		return std::nullopt;
	}

	void Font::Open()
	{
		FT_Error error;
		if (error = FT_Init_FreeType(&library))
		{
			throw std::runtime_error("Freetype failed to initialize");
		}

		auto path = Files::GetQualifiedPath(filename);

		if (!path.has_value())
		{
			Log::Error("Font could not be loaded: ", filename, '\n');
			return;
		}

		error = FT_New_Face(library, path.value().c_str(), 0, &face);
		if (error != 0)
		{
			throw std::runtime_error("Freetype failed to create face from memory");
		}

		// Multiply pixel size by 64 as FreeType uses points instead of pixels internally.
		error = FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
		if (error != 0)
		{
			throw std::runtime_error("Freetype failed to set char size");
		}
	}

	void Font::Close()
	{
		if (!IsOpen())
		{
			return;
		}
		FT_Done_Face(face);
		face = nullptr;
		FT_Done_FreeType(library);
		library = nullptr;
	}

	void Font::Load()
	{
		if (filename.empty()) return;

#ifdef ZAE_DEBUG
		auto debugStart = Time::Now();
#endif

		Open();

		auto bitmapSize = Vector2ui(1024);
		auto bitmap = std::make_unique<Bitmap>(bitmapSize);

		auto& bitmapData = bitmap->GetData();

		for (auto y = 0; y < bitmapSize.y; ++y)
		{
			for (auto x = 0; x < bitmapSize.x; ++x) 
			{
				bitmapData[(y * bitmapSize.x + x) * 4 + 0] = 0;
				bitmapData[(y * bitmapSize.x + x) * 4 + 1] = 0;
				bitmapData[(y * bitmapSize.x + x) * 4 + 2] = 0;
				bitmapData[(y * bitmapSize.x + x) * 4 + 3] = 255;
			}
		}

		const int MARGIN = 2;
		Vector2i pen;
		int currentMaxY = 0;

		auto glyphSlot = face->glyph;

		for (auto c : CHARACTERS)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				// error message
				continue;
			}

			const FT_Error loadCharError = FT_Render_Glyph(glyphSlot, FT_RENDER_MODE_SDF);
			if (loadCharError != 0)
			{
				continue;
			}

			const auto nextX = pen.x + MARGIN + MARGIN + face->glyph->bitmap.width;
			if (nextX >= bitmapSize.x)
			{
				pen.x = 0;
				pen.y = currentMaxY;
			}

			indices.insert({ c, glyphs.size() });
			glyphs.emplace_back(
				Glyph{
					.sizeX = (int)face->glyph->bitmap.width,
					.sizeY = (int)face->glyph->bitmap.rows,
					.bearingX = (int)face->glyph->bitmap_left,
					.bearingY = (int)face->glyph->bitmap_top,
					.advance = (int)face->glyph->advance.x,
					.textureX = (int)pen.x,
					.textureY = (int)pen.y
				});

			for (int texY = 0; texY < face->glyph->bitmap.rows; ++texY)
			{
				for (int texX = 0; texX < face->glyph->bitmap.width; ++texX)
				{
					Vector2i bitmapPosition = Vector2i(texX, texY) + pen + Vector2i(MARGIN);

					bitmapData[(bitmapPosition.y * bitmapSize.x + bitmapPosition.x) * 4 + 0] = face->glyph->bitmap.buffer[texY * face->glyph->bitmap.width + texX];
				}
			}

			pen.x += MARGIN + MARGIN + face->glyph->bitmap.width;

			currentMaxY = std::max(currentMaxY, (int)(pen.y + MARGIN + MARGIN + face->glyph->bitmap.rows));

		}

		image = std::make_unique<Image2d>(std::move(bitmap));

		// TODO: Is this actually valid??? - only needed for Image2dArray???
		/*image->InstanceTransitionImageLayout(
			image->GetImage(),
			image->GetFormat(),
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VK_IMAGE_ASPECT_COLOR_BIT,
			image->GetMipLevels(),
			0,
			1,
			0);*/

#ifdef ZAE_DEBUG
		Log::Out("Font Type ", filename, " loaded ", glyphs.size(), " glyphs in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif
	}
}