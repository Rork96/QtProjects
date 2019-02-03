project (QuaZip)
cmake_minimum_required(VERSION 2.8)

#find_package(Qt5Core)
#find_package(ZLIB)

#set (CMAKE_PREFIX_PATH "C:/Qt/5.10.1/msvc2017_64/")
#find_package (Qt5 COMPONENTS Core REQUIRED)

#set (ZLIB_LIBRARY zlib)
#include_directories (${PROJECT_SOURCE_DIR}/quazip/zlib)
#if (WIN32)
#    link_directories(${PROJECT_SOURCE_DIR}/quazip/zlib/library)
#elseif (UNIX)
#    link_directories(${PROJECT_SOURCE_DIR}/quazip/zlib/lib)
#endif ()

#include_directories(${Qt5Core_INCLUDE_DIRS})

# All build libraries are moved to this directory
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)")
#set(LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name" FORCE)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Tests)
#set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(quazip)
