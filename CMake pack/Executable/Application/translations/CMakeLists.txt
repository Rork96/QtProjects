# Create translations
set (TRANSLATIONS_PATH "${SOURCE_DIR}/translations")
foreach (LANGUAGE ${LANGUAGES})
    set (TRANSLATIONS ${TRANSLATIONS_PATH}/${LANGUAGE}.ts)
    qt5_create_translation (Q_FILES ${SOURCE_DIR}/src ${SOURCE_DIR}/include ${TRANSLATIONS} OPTIONS -no-obsolete -I ${SOURCE_DIR}/translations)
endforeach ()
add_custom_target (translate DEPENDS ${Q_FILES})
