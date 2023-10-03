SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
)

exampleTestApplication("ZaeEngineTest" "EngineTest.cpp" "${MODULE_LIBS}")