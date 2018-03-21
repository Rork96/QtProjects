cmake_minimum_required (VERSION 3.1)

# Project
project (Summerys LANGUAGES CXX)

add_subdirectory (Sum)
add_subdirectory (Summery)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Linux)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)