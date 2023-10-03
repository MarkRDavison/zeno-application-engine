#pragma once

#include <string_view>

namespace zae
{
	constexpr std::string_view ZAE_VERSION = "0.0.1";
	constexpr uint8_t ZAE_VERSION_MAJOR = 0;
	constexpr uint8_t ZAE_VERSION_MINOR = 0;
	constexpr uint8_t ZAE_VERSION_PATCH = 1;

	constexpr std::string_view ZAE_COMPILED_COMPILER = "C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/Tools/MSVC/14.35.32215/bin/Hostx64/x64/cl.exe";
	constexpr std::string_view ZAE_COMPILED_SYSTEM = "Windows-10.0.22621";
	constexpr std::string_view ZAE_COMPILED_GENERATOR = "Ninja";
	constexpr std::string_view ZAE_COMPILED_COMMIT_HASH = "2ff8adee3";
	constexpr std::string_view ZAE_COMPILED_BRANCH = "master";

	constexpr std::string_view ZAE_RESOURCES_DEV = "F:/Workspace/Git/zeno-application-engine/data";
	constexpr std::string_view ZAE_RESOURCES_DEV_LAPTOP = "C:/Workspace/Git/zeno-application-engine/data";
}