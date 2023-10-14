SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
	"zae-game${LIB_EXTENSION_SHARED}"
)

SET(CPP_FILES
    "Gui.cpp"
	"GuiApp.cpp"
	"GuiRenderer.cpp"
	"Scenes/GuiScene.cpp"
	"Ui/Panels.cpp"
)

exampleApplication("ZaeGuiExample" "${CPP_FILES}" "${MODULE_LIBS}")