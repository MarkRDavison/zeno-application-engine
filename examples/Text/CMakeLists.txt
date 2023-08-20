SET(MODULE_LIBS
	"zae-core${LIB_EXTENSION_SHARED}"
	"zae-engine${LIB_EXTENSION_SHARED}"
)

SET(CPP_FILES
    "text.cpp"
	"TextApp.cpp"
	"TextRenderer.cpp"
)

exampleApplication("ZaeTextExample" "${CPP_FILES}" "${MODULE_LIBS}")