cmake_minimum_required (VERSION 3.1)

# Project
project (Summerys LANGUAGES CXX)

# Dependent on build type and operation system,
# put exe-file and lib in one of the next folders
set (BINDIR bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY     ../../../../${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set (LIBRARY_OUTPUT_PATH                ../../../../${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

# Librarys names
set (LIBRARIES Summery)
foreach (LIB ${LIBRARIES})
    add_subdirectory (${LIB})
endforeach ()

# Executables names
set (APPLICATIONS Sum)
foreach (APP ${APPLICATIONS})
    add_subdirectory (${APP})
endforeach ()

# Install
# For complete deploying application drad app onto DeployQt script
# it will run windeployqt or linuxdeployqt to collect Qt librarys
# For Windows for MSVC copy vcredist from Qt\vcredist to deploy
# On Linux all libraries must be copied to folder deploy/lib
if (WIN32)
    set (EXT "bat")
    # Only for Windows, in Linux linuxdeployqt will create it
    install(FILES ${PROJECT_SOURCE_DIR}/scripts/qt.conf
            DESTINATION "${PROJECT_SOURCE_DIR}/deploy")
elseif (UNIX)
    set (EXT "sh")
endif ()
file (GLOB FILES ${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/*)
install(FILES ${FILES}
        DESTINATION "${PROJECT_SOURCE_DIR}/deploy")

install(FILES ${PROJECT_SOURCE_DIR}/scripts/DeployQt.${EXT}
        DESTINATION "${PROJECT_SOURCE_DIR}/deploy")
