cmake_minimum_required (VERSION 3.1)

# Library
project (LibName LANGUAGES CXX)

# Application icon and information
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/info)
include (generate_product_version)
generate_product_version (
        VersionFilesOutputVariable
        NAME ${PROJECT_NAME}
        VERSION_MAJOR 1
        VERSION_MINOR 0
        VERSION_PATH ${BUILD_COUNTER}
        VERSION_REVISION ${BUILD_REVISION}
        COMPANY_NAME "Company"
        FILE_DESCRIPTION "Library description"
)

#Qt modules
set (QT_MODULES
                    Core
#                    Gui
#                    Widgets
#                    PrintSupport
#                    Qml
#                    Quick
                    )

# Path to Qt library
if (WIN32)
    if (MINGW)  # MINGW 64 bit
        set (CMAKE_PREFIX_PATH "C:/msys64/mingw64/")
    elseif (MSVC)   # MSVC 64 bit
        set (CMAKE_PREFIX_PATH "C:/Qt/5.10.1/msvc2017_64/")
    else()  # MINGW 32 bit
        set (CMAKE_PREFIX_PATH "C:/Qt/5.10.1/mingw53_32/")
    endif ()
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
# C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (MINGW) # MINGW 64 bit
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

# Find dependencies Qt
find_package (Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Dependent on build type and operation system,
# put library in one of the next folders
if (MINGW)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_HOST_SYSTEM_NAME}/MinGW/${CMAKE_BUILD_TYPE})
elseif (MSVC)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_HOST_SYSTEM_NAME}/MSVC/${CMAKE_BUILD_TYPE})
endif()

# Create library
if (WIN32)
    add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${VersionFilesOutputVariable})

    # Qt modules
    qt5_use_modules (${PROJECT_NAME} ${QT_MODULES})
else ()
    add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

    # Qt modules
    qt5_use_modules (${PROJECT_NAME} ${QT_MODULES})
endif ()