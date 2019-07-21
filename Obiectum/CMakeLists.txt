cmake_minimum_required (VERSION 2.8)
project (test)

#version number
set (CMakeHelloWorld_VERSION_MAJOR 1)
set (CMakeHelloWorld_VERSION_MINOR 0)

#include the subdirectory containing our libs
add_subdirectory (src)
include_directories(src)
#indicate the entry point for the executable
add_executable (test src main.cpp)

# Indicate which libraries to include during the link process.
target_link_libraries (test obiectum)

install (TARGETS obiectum DESTINATION bin)