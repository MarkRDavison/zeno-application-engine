SET(MODULE_LIBS
	glfw
    volk::volk
	${GLSLANG_LIBRARIES}
	${FREETYPE_LIBRARIES}
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
)

SET(INCLUDE_DIRS
	"${PROJECT_SOURCE_DIR}/lib/core/include"
	"${PROJECT_SOURCE_DIR}/lib/engine/include"
)

submodule("Game" "${MODULE_LIBS}" "${INCLUDE_DIRS}")