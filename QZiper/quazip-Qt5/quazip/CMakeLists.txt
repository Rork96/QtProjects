cmake_minimum_required (VERSION 3.1)

project (QuaZip)

# set all include directories for in and out of source builds
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${ZLIB_INCLUDE_DIR}
)

file(GLOB SRCS "*.c" "*.cpp")
file(GLOB PUBLIC_HEADERS "*.h")

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

find_package (Qt5 COMPONENTS Core REQUIRED)

set (ZLIB_LIBRARY zlib)
include_directories (${PROJECT_SOURCE_DIR}/zlib)
if (WIN32)
	link_directories(${PROJECT_SOURCE_DIR}/zlib/library)
elseif (UNIX)
	link_directories(${PROJECT_SOURCE_DIR}/zlib/lib)
endif ()


# Must be added to enable export macro
ADD_DEFINITIONS(-DQUAZIP_BUILD)

#set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINDIR})

qt5_wrap_cpp(MOC_SRCS ${PUBLIC_HEADERS})
set(SRCS ${SRCS} ${MOC_SRCS})

# ----------------------------------------------------------------------------
# All build libraries are moved to this directory
if (WIN32)
	set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/library)
elseif (UNIX)
	set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
endif ()
# ----------------------------------------------------------------------------

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)")
set(LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name" FORCE)

add_library(quazip SHARED ${SRCS})
#set_target_properties(quazip PROPERTIES VERSION 1.0.0 SOVERSION 1)
target_link_libraries(quazip Qt5::Core ${ZLIB_LIBRARY})

#install(FILES ${PUBLIC_HEADERS} DESTINATION include/quazip)
#install(TARGETS quazip LIBRARY DESTINATION ${LIB_DESTINATION} ARCHIVE DESTINATION ${LIB_DESTINATION} RUNTIME DESTINATION ${LIB_DESTINATION})
