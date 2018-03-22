cmake_minimum_required(VERSION 3.7)
# Get project name from list ("0" - first element)
list (GET APPLICATIONS 0 APP_NAME)
# Project Test
project (${APP_NAME} LANGUAGES CXX)
# C++11
set(CMAKE_CXX_STANDARD 11)
# Clang ++
SET (CMAKE_CXX_COMPILER clang++)
# Flags
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
# AUTOMOC
set(CMAKE_AUTOMOC ON)
# Find includes in  build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#Qt modules
set(QT_MODULES Core Test)
# Path to Qt library
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "/opt/Qt/5.10.1/gcc_64/")
endif()
# Find dependencies Qt (QtCore, QtTest)
find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)
# Target properties (see main CMakeList)
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
# Sources
set(SOURCE_FILES Test_MyClass.cpp ../MyClass.h Test_MyClass.cpp Test_MyClass.h)
# Create executable file
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# Qt modules
qt5_use_modules(${PROJECT_NAME} ${QT_MODULES})
