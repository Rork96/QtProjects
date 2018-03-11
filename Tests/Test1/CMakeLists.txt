cmake_minimum_required(VERSION 3.7)
# Project Test
project(Test1 LANGUAGES CXX)
# C++11
set(CMAKE_CXX_STANDARD 11)
# Clang ++
SET (CMAKE_CXX_COMPILER clang++)
# Flags
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
# AUTOMOC
set(CMAKE_AUTOMOC ON)
# Find includes in  build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Find dependencies Qt (QtCore, QtTest)
find_package(Qt5 COMPONENTS Core Test REQUIRED)
# Compilation flags for Qt project
set(CMAKE_CXX_FLAGS "${QT_EXECUTABLE_COMPILE_FLAGS}")
# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/MyCalss)
# Sources
set(SOURCE_FILES Test_MyClass.cpp ../MyClass.h)
# Create executable file
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# Qt modules
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Test)
