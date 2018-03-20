cmake_minimum_required(VERSION 3.1)

# Project
project(QImageViewer LANGUAGES CXX)

# Application icon and information
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/info)
include(generate_product_version)
generate_product_version(
        VersionFilesOutputVariable
        NAME ${PROJECT_NAME}
        ICON ${PROJECT_SOURCE_DIR}/pict/${PROJECT_NAME}.ico
        VERSION_MAJOR 1
        VERSION_MINOR 0
        VERSION_PATH ${BUILD_COUNTER}
        VERSION_REVISION ${BUILD_REVISION}
        COMPANY_NAME "masterarrow"
        FILE_DESCRIPTION "Image Viewer"
)

#Qt modules
set(QT_MODULES Widgets PrintSupport)

# Path to Qt library
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "/opt/Qt/5.10.1/gcc_64/")
endif()

# Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find includes in  build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Run moc when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Clang as C compiller
SET (CMAKE_C_COMPILER             clang)
# Initialize CFLAGS.
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

# Use Clang++ as C++ compiller
SET (CMAKE_CXX_COMPILER            clang++)
# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Automatically find all files *.cpp, *.h, *.ui, *.qrc in project directory
FILE(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
FILE(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)
FILE(GLOB UI_SRC_FILES ${PROJECT_SOURCE_DIR}/*.ui)
FILE(GLOB UI_QRCS ${PROJECT_SOURCE_DIR}/*.qrc)

# Find dependencies Qt
find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Resources *.qrc
qt5_add_resources(UI_RESOURCES_RCC ${UI_QRCS})

# Dependent on build type and operation system,
# put exe-file in one of the next folders
#if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Windows/${CMAKE_BUILD_TYPE})
        set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Windows/dll/${CMAKE_BUILD_TYPE})
    elseif(UNIX)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Linux/${CMAKE_BUILD_TYPE})
        set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Linux/lib/${CMAKE_BUILD_TYPE})
    endif()
#endif()

# Create executable file
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC} ${VersionFilesOutputVariable})

    # Qt modules
    qt5_use_modules(${PROJECT_NAME} ${QT_MODULES})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC})

    # Qt modules
    qt5_use_modules(${PROJECT_NAME} ${QT_MODULES})

    # Install
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT depends
        RUNTIME DESTINATION "opt/${PROJECT_NAME} "
        LIBRARY DESTINATION "opt/${PROJECT_NAME}/lib"
        ARCHIVE DESTINATION "opt/${PROJECT_NAME}/lib")

    INSTALL(FILES ${PROJECT_SOURCE_DIR}/pict/${PROJECT_NAME}.png
        DESTINATION "usr/share/pixmaps")
    INSTALL(FILES ${PROJECT_SOURCE_DIR}/scripts/${PROJECT_NAME}.desktop
        DESTINATION "usr/share/applications")
endif()
