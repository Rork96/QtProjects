cmake_minimum_required (VERSION 3.1)

# Project
project (ProjectName LANGUAGES CXX)

# Dependent on build type and operation system,
# put exe-file and lib in one of the next folders
set (BINDIR bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY     ../../../${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set (LIBRARY_OUTPUT_PATH                ../../../${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

# Librarys names
set (LIBRARIES LibName1 LibName2 ...)
foreach (LIB ${LIBRARIES})
    add_subdirectory (${LIB})
endforeach ()

# Executables names
set (APPLICATIONS AppName1 AppName2 ...)
foreach (APP ${APPLICATIONS})
    add_subdirectory (${APP})
endforeach ()