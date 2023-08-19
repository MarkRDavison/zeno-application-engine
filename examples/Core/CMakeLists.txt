SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
)

exampleApplication("ZaeCoreExample" "core.cpp" "${MODULE_LIBS}")