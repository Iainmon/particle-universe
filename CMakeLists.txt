cmake_minimum_required(VERSION 2.8.9)
project (partical_universe)
add_executable(binary src/main.cpp)

add_custom_target(run
    COMMAND binary
    DEPENDS binary
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

target_link_libraries(binary "-framework OpenGL" "-framework GLUT" "-framework Cocoa" "-framework Foundation")