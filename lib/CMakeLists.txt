cmake_minimum_required(VERSION 2.8.9)
project (obiectum)
add_executable(test tests/main.cpp)


add_custom_target(run
    COMMAND test
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)