# BSD-3 Clause.
# Copyright (C) 2018 Antony Jr.
# -------------------------------
#  CMake Support for QArchive.
# -------------------------------

CMAKE_MINIMUM_REQUIRED( VERSION 3.2)
project(QArchive)

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

set (LIB_ARCHIVE archive)
include_directories (${PROJECT_SOURCE_DIR}/libarchive/libarchive)
#if (LINUX)
    add_subdirectory (${PROJECT_SOURCE_DIR}/libarchive)
#endif ()
link_directories(${PROJECT_SOURCE_DIR}/library)

# To simplify deployment use MS Compiller for Windows
# GCC or Clang for Linux
if (NOT MSVC) # MINGW or Clang
    # Use Clang as C compiller
    #set (CMAKE_C_COMPILER               clang)
    # Initialize CFLAGS.
    set (CMAKE_C_FLAGS                  "-Wall -std=c99")
    set (CMAKE_C_FLAGS_DEBUG            "-g")
    set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
    set (CMAKE_C_FLAGS_RELEASE          "-O3 -DNDEBUG")
    set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")

    # Use Clang++ as C++ compiller
    #set (CMAKE_CXX_COMPILER             clang++)
    # Initialize CXXFLAGS.
    set (CMAKE_CXX_FLAGS                "-Wall -std=c++11")
    set (CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
    set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE        "-O6 -DNDEBUG")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find the QtCore library.
find_package(Qt5Core)
find_package(Qt5Concurrent)

# Include Directories.
include_directories(.)
include_directories(include)

# Target properties (see main CMakeList)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINDIR})

#if (WIN32)
#    set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/library)
#elseif (UNIX)
#    set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#endif ()

add_library(QArchive src/QArchive.cc include/QArchive.hpp)
#add_library (QArchive SHARED src/QArchive.cc include/QArchive.hpp)
target_link_libraries(QArchive PUBLIC Qt5::Core Qt5::Concurrent ${LIB_ARCHIVE})
target_include_directories(QArchive PUBLIC . include)
