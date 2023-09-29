SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
)

SET(CPP_FILES
    "game.cpp"
	"GameApp.cpp"
	"GameRenderer.cpp"
	"Subrenders/ModelSubrender.cpp"
)

exampleApplication("ZaeGameExample" "${CPP_FILES}" "${MODULE_LIBS}")