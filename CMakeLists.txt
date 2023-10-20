cmake_minimum_required(VERSION 3.21)
project(Comparator)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)

option(BUILD_TESTS "Testing mode" OFF)

add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(testing)
endif()

