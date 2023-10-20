cmake_minimum_required(VERSION 3.21)
project(Comparator)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_compile_options(-Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)
add_executable(untitled src/main.cpp src/Comparator.cpp)
