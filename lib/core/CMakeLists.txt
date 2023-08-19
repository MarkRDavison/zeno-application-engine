SET(MODULE_LIBS

)

SET(INCLUDE_DIRS
	"${PROJECT_SOURCE_DIR}/lib/core/include"
)

submodule("Core" "${MODULE_LIBS}" "${INCLUDE_DIRS}")