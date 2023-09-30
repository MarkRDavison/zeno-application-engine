SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
	"zae-game${LIB_EXTENSION_SHARED}"
)

SET(CPP_FILES
    "game.cpp"
	"GameApp.cpp"
	"GameRenderer.cpp"
	"Scenes/Game3DScene.cpp"
	"Subrenders/Game3DSceneSubrender.cpp"
)

exampleApplication("ZaeGameExample" "${CPP_FILES}" "${MODULE_LIBS}")