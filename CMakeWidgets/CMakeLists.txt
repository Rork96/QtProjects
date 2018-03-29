cmake_minimum_required (VERSION 3.1)

# Project
project (CMakeWidgets LANGUAGES CXX)

# Application icon and information
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/info)
include (generate_product_version)
generate_product_version (
        VersionFilesOutputVariable
        NAME ${PROJECT_NAME}
        ICON ${PROJECT_SOURCE_DIR}/pict/${PROJECT_NAME}.ico
        VERSION_MAJOR 1
        VERSION_MINOR 0
        VERSION_PATH ${BUILD_COUNTER}
        VERSION_REVISION ${BUILD_REVISION}
        COMPANY_NAME "masterarrow"
        FILE_DESCRIPTION "CMakeWidgets"
)

#Qt modules
include (cmake/DeployQt5.cmake)
set (QT_MODULES
                    Core
                    Gui
                    Widgets
#                    Qml
#                    Quick
                    )
set (QML_PLUGINS
#                    QtQuick2
                    )
set (Qt_ImageFormats
#                    qjpeg
#                    qgif
#                    qwbmp
#                    qmng
                    )
#set (DRIVERS
#                qsqlite
#                qsqlmysql
#                qsqlpsql
#                )

# Path to Qt library
if (WIN32)
    set (CMAKE_PREFIX_PATH "C:/msys64/mingw64/")
elseif (UNIX)
    set (CMAKE_PREFIX_PATH "/opt/Qt/5.10.1/gcc_64/")
endif ()

# Release by default
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Find includes in  build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Run moc when necessary
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
# C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Clang as C compiller
set (CMAKE_C_COMPILER               clang)
# Initialize CFLAGS.
set (CMAKE_C_FLAGS                  "-Wall -std=c99")
set (CMAKE_C_FLAGS_DEBUG            "-g")
set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE          "-O3 -DNDEBUG")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")

# Use Clang++ as C++ compiller
set (CMAKE_CXX_COMPILER             clang++)
# Initialize CXXFLAGS.
set (CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set (CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Automatically find all files *.cpp, *.h, *.ui, *.qrc in project directory
file (GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file (GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)
file (GLOB UI_SRC_FILES ${PROJECT_SOURCE_DIR}/*.ui)
file (GLOB UI_QRCS ${PROJECT_SOURCE_DIR}/*.qrc)

# Find dependencies Qt
find_package (Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Resources *.qrc
qt5_add_resources (UI_RESOURCES_RCC ${UI_QRCS})

# Dependent on build type and operation system,
# put exe-file in one of the next folders
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

# Create executable file
if (WIN32)
    add_executable (${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC} ${VersionFilesOutputVariable})

    # Qt modules and librarys
    qt5_use_modules (${PROJECT_NAME} ${QT_MODULES})

    # Get path to windeployqt for deploying app
    get_target_property (QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component (QT_PATH ${QT5_QMAKE_EXECUTABLE} PATH)
    set (MAKE_PATH "${QT_PATH}/mingw32-make.exe")

    # Deploying Release version
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${MAKE_PATH} ARGS install)
    endif ()
else ()
    add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC})

    # Qt modules and librarys
    qt5_use_modules (${PROJECT_NAME} ${QT_MODULES})

    # Install in system folder
    #system_install ()

    # Deploying Release version
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND make ARGS install)
    endif ()
endif ()

# Install
set (dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#if (${QML_PLUGINS} NOT STREQUAL "")
#    install (DIRECTORY qml DESTINATION ${dir})
#endif()
#install_qt5_platform (${dir})
#install_qt5_V8 (${dir})
install_qt5_lib (${dir} ${QT_MODULES})
install_qt5_icu (${dir})
install_qt5_imageformats (${dir} ${Qt_ImageFormats})
install_qt5_qml_plugin (${dir} ${QML_PLUGINS})
install_qt5_dbdrivers (${dir} ${DRIVERS})
install_rt (${dir})
