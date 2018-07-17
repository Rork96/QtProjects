# Create translations
set (TRANSLATIONS_PATH "${PROJECT_SOURCE_DIR}/QBuilder/translations")
foreach (LANGUAGE ${LANGUAGES})
    set (TRANSLATIONS ${TRANSLATIONS_PATH}/${LANGUAGE}.ts)
    qt5_create_translation (Q_FILES ${PROJECT_SOURCE_DIR}/QBuilder/src ${TRANSLATIONS} OPTIONS -no-obsolete -I ${PROJECT_SOURCE_DIR}/QBuilder/translations)
endforeach ()
add_custom_target (translate DEPENDS ${Q_FILES})
