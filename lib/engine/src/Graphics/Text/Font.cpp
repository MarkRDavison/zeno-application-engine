#include <zae/Engine/Graphics/Text/Font.hpp>

#include <zae/Engine/Graphics/Text/tiny_msdf.hpp>
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
		auto fileLoaded = Files::ReadBytes(filename);

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

		auto layerCount = CHARACTERS.size();

		image = std::make_unique<Image2dArray>(Vector2ui(size, size), (uint32_t)layerCount, VK_FORMAT_R32G32B32A32_SFLOAT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		tinymsdf::Bitmap<float, 4> mtsdf(size, size);
		glyphs.resize(layerCount);

		for (auto c : CHARACTERS)
		{
			bool success = !tinymsdf::GenerateMTSDF(mtsdf, face, c);

			const FT_UInt glyphIndex = FT_Get_Char_Index(face, c);
			const FT_Error loadGlyphError = FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);

			auto id = indices.size();
			indices[c] = id;

			glyphs[id].advance = F26DOT6_TO_DOUBLE(face->glyph->metrics.horiAdvance);
			glyphs[id].bearingX = F26DOT6_TO_DOUBLE(face->glyph->metrics.horiBearingX);
			glyphs[id].bearingY = F26DOT6_TO_DOUBLE(face->glyph->metrics.horiBearingY);
			glyphs[id].width = F26DOT6_TO_DOUBLE(face->glyph->metrics.width);
			glyphs[id].height = F26DOT6_TO_DOUBLE(face->glyph->metrics.height);
			glyphs[id].layer = id;

			if (success)
			{
				image->SetPixels(mtsdf.pixels, id);
			}
		}

		// TODO: Is this actually valid???
		image->InstanceTransitionImageLayout(
			image->GetImage(),
			image->GetFormat(),
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
			VK_IMAGE_ASPECT_COLOR_BIT,
			image->GetMipLevels(),
			0,
			layerCount,
			0);

#ifdef ZAE_DEBUG
		Log::Out("Font Type ", filename, " loaded ", glyphs.size(), " glyphs in ", (Time::Now() - debugStart).AsMilliseconds<float>(), "ms\n");
#endif
	}
}