cmake_minimum_required (VERSION 3.1)

# Project
project (Tests LANGUAGES CXX)

# Dependent on operation system,
# put exe-file in one of the next folders
set (BINDIR bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY     ../../${CMAKE_HOST_SYSTEM_NAME}/MyClass)

# Test names
set (APPLICATIONS Test1 Test2 Test3)
foreach (APP ${APPLICATIONS})
    add_subdirectory (${APP})
endforeach ()
