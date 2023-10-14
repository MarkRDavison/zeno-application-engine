#pragma once

#include <filesystem>

#include <zae/Core/Utils/NonCopyable.hpp>

struct GLFWcursor;

namespace zae
{
	enum class CursorHotspot : uint8_t
	{
		UpperLeft,
		UpperRight,
		BottomLeft,
		BottomRight,
		Centered
	};

	enum class CursorStandard : uint32_t
	{
		Arrow = 0x00036001,
		IBeam = 0x00036002,
		Crosshair = 0x00036003,
		Hand = 0x00036004,
		ResizeX = 0x00036005,
		ResizeY = 0x00036006
	};

	class Cursor : NonCopyable
	{
		friend class Window;
	public:
		/**
		 * Sets the cursor to a image file.
		 * @param filename The new custom mouse file.
		 * @param hotspot The hotspot to display the cursor image at.
		 */
		Cursor(const std::filesystem::path& filename, CursorHotspot hotspot);
		/**
		 * Sets the cursor to a system style.
		 * @param standard The standard shape.
		 */
		Cursor(CursorStandard standard);
		~Cursor();

	private:
		GLFWcursor* cursor = nullptr;
	};
}
