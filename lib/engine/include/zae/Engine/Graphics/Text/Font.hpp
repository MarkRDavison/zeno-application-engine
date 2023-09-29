#pragma once

#include <zae/Engine/Resources/Resource.hpp>
#include <zae/Engine/Graphics/Images/Image2dArray.hpp>
#include <zae/Engine/Graphics/Pipelines/PipelineGraphics.hpp>

typedef struct FT_LibraryRec_* FT_Library;
typedef struct FT_FaceRec_* FT_Face;

namespace zae
{

	class Font : public Resource
	{
	public:
		class Glyph
		{
		public:
			float layer;
			float bearingX;
			float bearingY;
			float width;
			float height;
			float advance;
		};

		explicit Font(std::filesystem::path filename, std::size_t size = 64, bool load = true);
		~Font();

		std::optional<Glyph> GetGlyph(wchar_t ascii) const;

		std::type_index GetTypeIndex() const override { return typeid(Font); }

		const std::filesystem::path& GetFilename() const { return filename; }
		const Image2dArray* GetImage() const { return image.get(); }
		bool IsOpen() const noexcept { return library != nullptr; }

		template <typename T>
		T GetSpaceWidth() const { return GetGlyph(' ').value().width; }

		template <typename T>
		T GetSize() const { return static_cast<T>(size); }

	private:
		void Open();
		void Close();
		void Load();

		FT_Library library = nullptr;
		FT_Face face = nullptr;

		std::filesystem::path filename;
		std::unique_ptr<Image2dArray> image;

		/// Char to glyphs index.
		std::map<wchar_t, std::size_t> indices;
		std::vector<Glyph> glyphs;
		/// Glyph size in pixels.
		std::size_t size;

	};

}