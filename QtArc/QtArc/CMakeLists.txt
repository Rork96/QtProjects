cmake_minimum_required (VERSION 3.1)

# Get project name from list ("0" - first element)
list (GET APPLICATIONS 0 APP_NAME)

# Project
project (${APP_NAME} LANGUAGES CXX)

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
        FILE_DESCRIPTION "${APP_NAME} - Managing all types of archives"
)

#Qt modules
set (QT_MODULES
                    Core
                    Gui
                    Widgets
#                    PrintSupport
#                    Qml Quick Network # Network needed for QML
                    Concurrent
)

# Path to Qt library
if (WIN32)
    if (MINGW)  # MINGW 64 bit
        set (CMAKE_PREFIX_PATH "C:/msys64/mingw64/")
    elseif (MSVC)   # MSVC 64 bit
        set (CMAKE_PREFIX_PATH "C:/Qt/5.11.1/msvc2017_64/")
    else()  # MINGW 32 bit
        set (CMAKE_PREFIX_PATH "C:/Qt/5.11.1/mingw53_32/")
    endif ()
elseif (UNIX)
    set (CMAKE_PREFIX_PATH "/opt/Qt/5.11.1/gcc_64/")
endif ()

# Serch for librarys
#set (LIBRARIES QArchive)
#foreach (LIBRARY ${LIBRARIES})
#    include_directories (../${LIBRARY}/include)
#    link_directories(${LIBRARY_OUTPUT_PATH})
#endforeach ()

foreach (LIBRARY ${LIBRARIES})
    include_directories (../KArchive/src)
    link_directories(../library)
endforeach ()

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
# C++14
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# To simplify deployment use MS Compiller for Windows
# GCC or Clang for Linux
if (NOT MSVC) # MINGW or Clang
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
endif ()

# Automatically find all files *.cpp, *.h, *.ui, *.qrc in project directory
file (GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file (GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)
file (GLOB UI_SRC_FILES ${PROJECT_SOURCE_DIR}/*.ui)
file (GLOB UI_QRCS ${PROJECT_SOURCE_DIR}/*.qrc)

# Find dependencies Qt
find_package (Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Resources *.qrc
qt5_add_resources (UI_RESOURCES_RCC ${UI_QRCS})

# Target properties (see main CMakeList)
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})

# Create executable file
if (WIN32)
    add_executable (${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES}
            ${UI_SRC_FILES} ${UI_RESOURCES_RCC} ${VersionFilesOutputVariable})

    # Link librarys
    foreach (QT_MODULE ${QT_MODULES})
        target_link_libraries(${PROJECT_NAME} Qt5::${QT_MODULE} ${LIBRARIES})
    endforeach ()
else ()
    add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
            ${UI_SRC_FILES} ${UI_RESOURCES_RCC})

    # Link librarys
    foreach (QT_MODULE ${QT_MODULES})
        target_link_libraries(${PROJECT_NAME} Qt5::${QT_MODULE} ${LIBRARIES})
    endforeach ()
endif ()