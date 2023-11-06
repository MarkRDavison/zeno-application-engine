SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
	"zae-game${LIB_EXTENSION_SHARED}"
)

FILE(GLOB_RECURSE CPP_FILES "*.cpp")

exampleApplication("ZaeTowerDefenseExample" "${CPP_FILES}" "${MODULE_LIBS}")