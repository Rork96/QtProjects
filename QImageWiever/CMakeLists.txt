cmake_minimum_required(VERSION 3.1)

# Project
project(QImageWiever LANGUAGES CXX)

set(PROJECT_LONGNAME "QImageWiever")
set(PROJECT_VERSION "1.0.0")

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

# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Automatically find all files *.cpp, *.h, *.ui, *.qrc in project directory
FILE(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
FILE(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)
FILE(GLOB UI_SRC_FILES ${PROJECT_SOURCE_DIR}/*.ui)
FILE(GLOB UI_QRCS ${PROJECT_SOURCE_DIR}/*.qrc)
# For application icon for Windows
FILE(GLOB ICON_RCS ${PROJECT_SOURCE_DIR}/pict/*.rc)

# Find dependencies Qt (Widgets, QtGui, QtCore)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

# Add QtCore and QtGui include paths
include_directories(${QT_INCLUDES})

# Add -DQT_WIDGETS_LIB for QtWidgets in Qt
add_definitions(${QT_DEFINITIONS})

# Compilation flags for Qt project
set(CMAKE_CXX_FLAGS "${QT_EXECUTABLE_COMPILE_FLAGS}")

# Resources *.qrc
qt5_add_resources(UI_RESOURCES_RCC ${UI_QRCS})

# Dependent on build type and operation system,
# put exe-file in one of the next folders
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Win32)
        #set
    elseif(UNIX)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Linux)
    endif()
endif()

# Create executable file
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC} ${ICON_RCS})

    # Qt modules
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport)

    # Set executable file properties
    set_target_properties(${PROJECT} PROPERTIES
        PROJECT_LONGNAME ${PROJECT_LONGNAME}
        VERSION "${PROJECT_VERSION}" SOVERSION "0")
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
        ${UI_SRC_FILES} ${UI_RESOURCES_RCC})

    # Qt modules
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport)

    # Install
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT depends
        RUNTIME DESTINATION "opt/${PROJECT_NAME} "
        LIBRARY DESTINATION "opt/${PROJECT_NAME}/lib"
        ARCHIVE DESTINATION "opt/${PROJECT_NAME}/lib")

    INSTALL(FILES ${PROJECT_SOURCE_DIR}/pict/QImageWiever.png
        DESTINATION "usr/share/pixmaps")
    INSTALL(FILES ${PROJECT_SOURCE_DIR}/scripts/QImageWiever.sh
        DESTINATION "opt/${PROJECT_NAME}")
    INSTALL(FILES ${PROJECT_SOURCE_DIR}/scripts/Screaner.desktop
        DESTINATION "usr/share/applications")
endif()
