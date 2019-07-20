cmake_minimum_required(VERSION 2.8.9)
project (partical_universe)
add_executable(binary src/main.cpp)

add_custom_target(run
    COMMAND binary
    DEPENDS binary
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
elseif(UNIX AND APPLE)
    set(APPLE TRUE)
endif()

if(LINUX)
    link_directories(/usr/lib)
    target_link_libraries(binary "-lGL" "-lGLU" "-lglut" "-lGLEW")
elseif(APPLE)
    target_link_libraries(binary "-framework OpenGL" "-framework GLUT" "-framework Cocoa" "-framework Foundation")
endif()

