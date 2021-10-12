cmake_minimum_required(VERSION 3.5)

project(test01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("src")
add_subdirectory("inipp")
include_directories("src")
include_directories("inipp")
add_executable(test01 main.cpp)
target_link_libraries(test01 INTERFACE speech2text)
