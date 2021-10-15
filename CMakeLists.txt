cmake_minimum_required(VERSION 3.5)

project(test01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_FLAGS_DEBUG "-gfull -glldb")
set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CPPLINT "cpplint")

add_subdirectory("speech2text")

include_directories("speech2text")
include_directories("speech2text/inipp")
add_executable(test01 main.cpp)

find_package(Torch REQUIRED)

target_link_libraries(test01 speech2text)

target_sources(test01 PRIVATE config.ini)
