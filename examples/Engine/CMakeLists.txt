SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
)

SET(CPP_FILES
    "engine.cpp"
	"EngineApp.cpp"
	"EngineRenderer.cpp"
	"Subrenders/UiSubrender.cpp"
	"Subrenders/ModelSubrender.cpp"
)

exampleApplication("ZaeEngineExample" "${CPP_FILES}" "${MODULE_LIBS}")