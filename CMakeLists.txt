CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(zae CXX)

SET(ZAE_CXX_STANDARD 20)

SET(CMAKE_CXX_STANDARD ${ZAE_CXX_STANDARD})
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(CMAKE_DEBUG_POSTFIX "-d")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DZAE_DEBUG)
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
  CMAKE_POLICY(SET CMP0110 NEW)
endif()

find_package(Vulkan REQUIRED FATAL_ERROR)

# VOLK
add_subdirectory(thirdparty/volk)



# GLFW
find_package(glfw3 3.3.6 QUIET)
if(NOT TARGET glfw)
	foreach(_glfw3_option "GLFW_BUILD_TESTS" "GLFW_BUILD_EXAMPLES" "GLFW_BUILD_DOCS" "GLFW_INSTALL")
		set(${_glfw3_option} OFF CACHE INTERNAL "")
	endforeach()
	add_subdirectory(thirdparty/glfw glfw)
	set_target_properties(glfw PROPERTIES FOLDER "thirdparty")
endif()



# GLSLANG
# On MSVC shared mode must be disabled with glslang currently
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
if(MSVC)
	set(BUILD_SHARED_LIBS OFF)
endif()
set(ENABLE_SPVREMAPPER OFF CACHE INTERNAL "Enables building of SPVRemapper")
set(ENABLE_GLSLANG_BINARIES OFF CACHE INTERNAL "Builds glslangValidator and spirv-remap")
set(ENABLE_HLSL OFF CACHE INTERNAL "Enables HLSL input support")
set(ENABLE_RTTI ON CACHE INTERNAL "Enables RTTI")
set(ENABLE_EXCEPTIONS ON CACHE INTERNAL "Enables Exceptions")
set(ENABLE_CTEST OFF CACHE INTERNAL "Enables testing")
set(SKIP_GLSLANG_INSTALL ON CACHE INTERNAL "Skip installation")
add_subdirectory(thirdparty/glslang glslang)
set_target_properties(glslang PROPERTIES FOLDER "thirdparty/glslang")
#set_target_properties(glslang-build-info PROPERTIES FOLDER "thirdparty/glslang")
set_target_properties(GenericCodeGen PROPERTIES FOLDER "thirdparty/glslang")
set_target_properties(MachineIndependent PROPERTIES FOLDER "thirdparty/glslang")
set_target_properties(OGLCompiler PROPERTIES FOLDER "thirdparty/glslang")
set_target_properties(OSDependent PROPERTIES FOLDER "thirdparty/glslang")
set_target_properties(SPIRV PROPERTIES FOLDER "thirdparty/glslang")
set(GLSLANG_LIBRARIES glslang SPIRV)
# Reset back to value before MSVC fix
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")



# freetype
find_package(Freetype 2.11.1 QUIET)
if(NOT Freetype_FOUND)
	set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
	set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
	set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
	set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
	add_subdirectory(thirdparty/freetype freetype)
	
	set(FREETYPE_LIBRARIES "freetype")
endif()



ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(examples)
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)